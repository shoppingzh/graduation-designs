package com.littlezheng.android.checkwork;

import android.Manifest;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.JsonParseException;
import com.google.gson.reflect.TypeToken;
import com.littlezheng.android.checkwork.adapter.SignRecord;
import com.littlezheng.android.checkwork.adapter.SignRecordAdapter;
import com.littlezheng.android.checkwork.ble.BleCommunicator;
import com.littlezheng.android.checkwork.ble.BleDeviceHolder;
import com.littlezheng.android.checkwork.config.Urls;
import com.littlezheng.android.checkwork.model.Department;
import com.littlezheng.android.checkwork.model.Employee;
import com.littlezheng.android.checkwork.net.AjaxResult;
import com.littlezheng.android.checkwork.net.NetUtils;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    private ListView signRecordLv;
    private BleDeviceHolder bleDeviceHolder = new BleDeviceHolder(this, "BT05");
    private List<SignRecord> signRecords = new ArrayList<>();
    private SignRecordAdapter signRecordAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        signRecordLv = (ListView) findViewById(R.id.lv_sign_record);

        //地理位置授权
        if(ActivityCompat.checkSelfPermission(MainActivity.this,
                Manifest.permission.ACCESS_FINE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, 1);
        }
        if(ActivityCompat.checkSelfPermission(MainActivity.this,
                Manifest.permission.ACCESS_COARSE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, 2);
        }

        signRecordAdapter = new SignRecordAdapter(this,
                R.layout.item_signin, signRecords);
        signRecordLv.setAdapter(signRecordAdapter);


        listen();

        //连接蓝牙设备
        new Thread(new Runnable() {
            @Override
            public void run() {
                bleDeviceHolder.scanConnect();
            }
        }).start();
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        listen();
    }

    public void listen(){
        Log.d(TAG, "监听签到");
        BleCommunicator.setOnReceiveListener(new BleCommunicator.OnReceiveListener() {
            @Override
            public void onReceive(byte[] data) {
                if(data.length >= 6) {
                    if (data[0] == -75 && data[1] == -54 &&
                            data[2] == -126 && data[4] == -54 && data[5] == -75) {
                        int idx = (int)data[3] + 128;
                        Log.d(TAG, "模板id：" + idx);
                        NetUtils.get(Urls.URL_API + "sign_in?temp_idx=" + idx, new Callback() {
                            @Override
                            public void onFailure(Call call, IOException e) {

                            }

                            @Override
                            public void onResponse(Call call, Response response) throws IOException {
                                String resp = response.body().string();
                                Log.d(TAG, "响应：" + resp);
                                Gson gson = new Gson();
                                AjaxResult<Employee> result = null;

                                try{
                                    result = gson.fromJson(resp, new TypeToken<AjaxResult<Employee>>(){}.getType());
                                }catch (JsonParseException e){
                                    return;
                                }

                                if(result != null){
                                    if("0".equals(result.getCode())){
                                        Log.d(TAG, "员工：" + result.getData());
                                        Employee e = result.getData();
                                        final SignRecord record = new SignRecord();
                                        record.setName(e.getName());
                                        record.setDepartment(e.getDepartment().getName());
                                        record.setPhoneNum(e.getPhoneNum());
                                        record.setSignTime(new Date());
                                        signRecords.add(record);

                                        runOnUiThread(new Runnable() {
                                            @Override
                                            public void run() {
                                                signRecordAdapter.notifyDataSetChanged();
                                            }
                                        });
                                    }else{

                                    }
                                }

                            }
                        });
                    }
                }
            }
        });
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case R.id.item_add_employee:
                Intent intent = new Intent(this, WaitActivity.class);
                startActivity(intent);
                break;
        }
        return super.onOptionsItemSelected(item);
    }

}
