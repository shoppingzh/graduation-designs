package com.littlezheng.android.checkwork;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.littlezheng.android.checkwork.ble.BleCommunicator;
import com.littlezheng.android.checkwork.ble.BleDeviceHolder;

public class WaitActivity extends AppCompatActivity {

    private static final String TAG = "WaitActivity";

    private TextView tipsTv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wait);
        tipsTv = (TextView) findViewById(R.id.tv_tips);

        //发送切换采集模式命令
        BleDeviceHolder.getCommunicator().send(new byte[]{1});

        BleCommunicator.setOnReceiveListener(new BleCommunicator.OnReceiveListener() {
            @Override
            public void onReceive(final byte[] data) {
                if(data.length >= 6){
                    if(data[0] == -75 && data[1] == -54 &&
                            data[4] == -54 && data[5] == -75){
                        if(data[2] == -127){
                            int idx = (int)data[3] + 128;
                            collectSucc(idx);
                        }else if(data[2] == -1){
                            if(data[3] == -127){
                                haveThisEmployee();
                            }
                        }

                    }
                }
            }
        });

    }

    private void haveThisEmployee() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                tipsTv.setText("你已经是员工了，无需重复添加！");
            }
        });

        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        //转发到添加员工界面
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(WaitActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });
    }

    //指纹采集成功
    private void collectSucc(final int idx) {
        Log.d(TAG, "指纹采集成功！");

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                tipsTv.setText("指纹采集成功，模板id：" + idx);
            }
        });

        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        //转发到添加员工界面
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(WaitActivity.this, AddActivity.class);
                intent.putExtra("temp_idx", idx);
                startActivity(intent);
            }
        });
    }
}
