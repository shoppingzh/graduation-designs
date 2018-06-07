package com.littlezheng.ledmatrix;

import android.Manifest;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.littlezheng.ledmatrix.ble.BleTool;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    private static final String BT05_SERVICE_UUID = "0000ffe0-0000-1000-8000-00805f9b34fb";
    private static final String BT05_CHANNEL_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb";
    private static final String TAG = "MainActivity";

    private static final Map<String, byte[]> wordMap = new HashMap<>();

    private ProgressDialog progressDialog;
    private BroadcastReceiver bluetoothBr = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            switch(intent.getAction()){
                case BluetoothAdapter.ACTION_STATE_CHANGED:
                    int blueState = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE, 0);
                    switch(blueState){
                        case BluetoothAdapter.STATE_TURNING_ON:
                            break;
                        case BluetoothAdapter.STATE_ON:
                            //开始扫描
                            scanAndConnectBT05();
                            break;
                        case BluetoothAdapter.STATE_TURNING_OFF:
                            break;
                        case BluetoothAdapter.STATE_OFF:
                            break;
                    }
                    break;
            }
        }
    };

    private BluetoothAdapter bluetoothAdapter;
    private EditText wordsEt;
    private Button displayBtn;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        wordsEt = (EditText) findViewById(R.id.et_words);
        displayBtn = (Button) findViewById(R.id.btn_display);

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

        //显示连接进度条
        progressDialog = new ProgressDialog(this);
        progressDialog.setCancelable(false);
        progressDialog.setMessage("正在连接设备...");
        progressDialog.show();

        //开启蓝牙
        bluetoothAdapter = ((BluetoothManager) getSystemService(BLUETOOTH_SERVICE)).getAdapter();
        if(!bluetoothAdapter.isEnabled()){
            bluetoothAdapter.enable();
        }else{
            scanAndConnectBT05();
        }

        //注册蓝牙开启广播，当蓝牙开启时，连接BT05
        registerReceiver(bluetoothBr, new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED));

        //加载汉字编码
        loadCodes();

        //显示
        displayBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                displayWords();
            }
        });

    }

    /**
     * 显示汉字
     */
    private void displayWords() {
        String words = wordsEt.getText().toString();
        if(words == null || words.isEmpty())
            return;

        BleTool.send((byte)0xaa, (byte)0x55);
        for(int i=0;i<words.length();i++){
            String word = String.valueOf(words.charAt(i));
            Log.d(TAG, "文字：" + word);
            Log.d(TAG, "编码：" + Arrays.toString(wordMap.get(word)));
            byte[] codes = wordMap.get(word);
            if(codes != null){
                for(byte b : codes){
                    BleTool.send(b);
                    try {
                        Thread.sleep(50);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

        }

        BleTool.send((byte)0x55, (byte)0xaa);
    }

    /**
     * 加载汉字编码与wordMap映射中
     */
    private void loadCodes() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                InputStream in = null;
                InputStreamReader ir = null;
                BufferedReader br = null;
                try {
                    in  = getAssets().open("words");
                    ir = new InputStreamReader(in, "UTF-8");
                    br = new BufferedReader(ir);

                    String line = null;
                    while((line = br.readLine()) != null){
                        String parts[] = line.split(":");
                        String[] strCodes = parts[1].split(",");
                        if(strCodes != null){
                            byte[] codes = new byte[strCodes.length];
                            for(int i=0;i<strCodes.length;i++){
                                int code = Integer.valueOf(strCodes[i], 16);
                                codes[i] = (byte) code;
                            }
                            wordMap.put(parts[0], codes);
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }finally{
                    if(br != null){
                        try {
                            br.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                    if(ir != null){
                        try {
                            ir.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                    if(in != null){
                        try {
                            in.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }).start();
    }


    /**
     * 扫描并连接BT05
     *
     */
    private void scanAndConnectBT05() {
        bluetoothAdapter.getBluetoothLeScanner().startScan(new ScanCallback() {
            @Override
            public void onScanResult(int callbackType, ScanResult result) {
                super.onScanResult(callbackType, result);
                BluetoothDevice device = result.getDevice();
                if ("BT05".equals(device.getName())) {
                    //连接设备
                    BleTool.connectDevice(device, MainActivity.this, new BleTool.ConnectCallback() {
                        @Override
                        public void onConnect(BluetoothGatt gatt) {
                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    progressDialog.cancel();
                                    Toast.makeText(MainActivity.this, "BT05已连接！", Toast.LENGTH_SHORT).show();
                                }
                            });

                        }
                        @Override
                        public void onServicesDiscovered(List<BluetoothGattService> services) {
                            //选择通信通道
                            BleTool.chooseChannel(BT05_SERVICE_UUID, BT05_CHANNEL_UUID);
                        }
                    });

                }
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        BleTool.disconnect();
        unregisterReceiver(bluetoothBr);
        bluetoothAdapter.disable();
    }

}
