package com.littlezheng.smarthome;

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
import android.widget.CompoundButton;
import android.widget.SeekBar;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.littlezheng.smarthome.ble.BleTool;

import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final String BT05_SERVICE_UUID = "0000ffe0-0000-1000-8000-00805f9b34fb";
    private static final String BT05_CHANNEL_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb";
    private static final String TAG = "MainActivity";

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
    private ToggleButton hallLightBtn;
    private SeekBar bedroomLightSb;
    private ToggleButton fanBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        hallLightBtn = (ToggleButton) findViewById(R.id.btn_hall_light);
        bedroomLightSb = (SeekBar) findViewById(R.id.sb_bedroom_light);
        fanBtn = (ToggleButton) findViewById(R.id.btn_fan);

        //控制大厅灯的亮灭
        hallLightBtn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    BleTool.send(new byte[]{1});
                }else{
                    BleTool.send(new byte[]{0});
                }
            }
        });

        //控制卧室灯的亮度
        bedroomLightSb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                BleTool.send(new byte[]{(byte) (progress + 2)});
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        //控制风扇开启/关闭
        fanBtn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    BleTool.send(new byte[]{103});
                }else{
                    BleTool.send(new byte[]{102});
                }
            }
        });

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
