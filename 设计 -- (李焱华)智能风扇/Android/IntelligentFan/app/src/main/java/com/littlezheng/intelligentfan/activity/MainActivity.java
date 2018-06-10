package com.littlezheng.intelligentfan.activity;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattServer;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.littlezheng.intelligentfan.R;
import com.littlezheng.intelligentfan.activity.util.BleConnector;
import com.littlezheng.intelligentfan.activity.util.BleUtils;

import java.util.Arrays;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private static final UUID SERVICE_UUID = UUID.fromString("0000ffe0-0000-1000-8000-00805f9b34fb");
    private static final UUID CHARACTERISTIC_UUID = UUID.fromString("0000ffe1-0000-1000-8000-00805f9b34fb");
    private static final String TAG = "MainActivity";

    private BluetoothGatt mGatt;
    private BluetoothGattCharacteristic mCharacteristic;

    private SeekBar speedSb;
    private TextView speedTv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        speedSb = (SeekBar) findViewById(R.id.sb_speed);
        speedTv = (TextView) findViewById(R.id.tv_speed);

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

        BleConnector bleConnector = new BleConnector(this);
        bleConnector.setConnectListener(new BleConnector.BleConnectListener() {
            @Override
            public void onConnected(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                mGatt = gatt;
                mCharacteristic = characteristic;
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this, "蓝牙连接成功！", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
        bleConnector.setReadListener(new BleConnector.ReadListener() {
            @Override
            public void onRead(byte[] value) {

            }
        });
        bleConnector.connect("BT05");


        speedSb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                speedTv.setText("风速: " + progress);
                BleUtils.send(mGatt, mCharacteristic, (byte) progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

    }
}
