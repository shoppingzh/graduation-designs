package com.littlezheng.bleconnect;

import android.Manifest;
import android.annotation.TargetApi;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.support.annotation.NonNull;
import android.support.annotation.RequiresApi;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import com.littlezheng.bleconnect.Adapter.BleDeviceAdapter;
import com.littlezheng.bleconnect.Adapter.BleReceiveAdapter;
import com.littlezheng.bleconnect.entity.ReceiveInfo;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@TargetApi(Build.VERSION_CODES.LOLLIPOP)
@RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR2)
public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static final String TAG = "MainActivity";

    private BluetoothAdapter bluetoothAdapter;
    private List<BluetoothDevice> bleDevices = new ArrayList<>();
    private BleDeviceAdapter bleDeviceAdapter;
    private ScanCallback currentBleScanListener;

    private BluetoothGatt mGatt;
    private BluetoothGattCharacteristic mCharacteristic;

    //接收相关
    private BleReceiveAdapter receiveAdapter;
    private List<ReceiveInfo> receiveContents = new ArrayList<>(10);

    private EditText hexContentEt;
    private Button sendBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        hexContentEt = (EditText) findViewById(R.id.et_hex_content);
        sendBtn = (Button) findViewById(R.id.btn_send);
        sendBtn.setOnClickListener(this);

        //地理位置授权
        if(ActivityCompat.checkSelfPermission(MainActivity.this, Manifest.permission.ACCESS_FINE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, 1);
        }
        if(ActivityCompat.checkSelfPermission(MainActivity.this, Manifest.permission.ACCESS_COARSE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, 2);
        }

        //开启位置信息
        LocationManager locationManager = (LocationManager) getSystemService(LOCATION_SERVICE);
        if(! locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)){
            Toast.makeText(MainActivity.this, "位置信息未开启，请开启位置信息！", Toast.LENGTH_SHORT).show();
            Intent enableLocationIntent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
            startActivityForResult(enableLocationIntent, 1);
        }

        BluetoothManager bluetoothManager = (BluetoothManager) getSystemService(BLUETOOTH_SERVICE);
        bluetoothAdapter = bluetoothManager.getAdapter();
        //开启蓝牙
        if(!bluetoothAdapter.isEnabled()){
            /*AlertDialog alertDialog = new AlertDialog.Builder(this)
                    .setMessage("开启蓝牙")
                    .setCancelable(false)
                    .setNegativeButton("否", null)
                    .setPositiveButton("是", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            bluetoothAdapter.enable();
                            dialog.dismiss();
                        }
                    }).create();
            alertDialog.show();*/
            bluetoothAdapter.enable();
        }

        //设备列表
        ListView deviceLv = (ListView) findViewById(R.id.lv_ble_device);
        bleDeviceAdapter = new BleDeviceAdapter(MainActivity.this, R.layout.item_ble_device, bleDevices);
        deviceLv.setAdapter(bleDeviceAdapter);

        //接收信息列表
        ListView receiveContentsLv = (ListView) findViewById(R.id.lv_receive_contents);
        receiveAdapter = new BleReceiveAdapter(MainActivity.this,
                R.layout.item_ble_receive, receiveContents);
        receiveContentsLv.setAdapter(receiveAdapter);

        bleDeviceAdapter.setBleListener(new BleListener() {
            @Override
            public void onConnected(BluetoothGatt gatt) {
                showSendWindow();
            }

            @Override
            public void onDisconnected(BluetoothGatt gatt) {
                hideSendWindow();
            }

            @Override
            public void onCharacteristicGot(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                mGatt = gatt;
                mCharacteristic = characteristic;
            }

            @Override
            public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                receiveContents.add(new ReceiveInfo(characteristic.getValue(), new Date().getTime()));
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        receiveAdapter.notifyDataSetChanged();
                    }
                });
            }

            @Override
            public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {

            }
        });
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_send:
                String hexContent;
                if((hexContent = hexContentEt.getText().toString()).isEmpty()) return;
                String parts[] = hexContent.trim().split(" ");
                byte[] bytes = new byte[parts.length];
                int i = 0;
                for(String ele : parts){
                    byte b = 0;
                    try{
                        b = (byte)Integer.parseInt(ele, 16);
                    }catch (Exception e){
                        Toast.makeText(this, "请输入正确的16进制数值！", Toast.LENGTH_SHORT).show();
                        return;
                    }
                    bytes[i++] = b;
                }
                send(bytes);
                break;
        }
    }

    private void send(byte[] bytes) {
        mGatt.setCharacteristicNotification(mCharacteristic, true);
        mCharacteristic.setValue(bytes);
        mGatt.writeCharacteristic(mCharacteristic);
    }

    private void showSendWindow() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                findViewById(R.id.layout_send_window).setVisibility(View.VISIBLE);
            }
        });
    }

    private void hideSendWindow() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                findViewById(R.id.layout_send_window).setVisibility(View.GONE);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode){
            case 1:
                if(!((LocationManager)getSystemService(LOCATION_SERVICE)).
                        isProviderEnabled(LocationManager.GPS_PROVIDER)){
                    Toast.makeText(MainActivity.this, "位置信息开启失败，请重新开启！", Toast.LENGTH_SHORT).show();
                }
                break;
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode){
            case 1:
            case 2:
//                if(grantResults.length <= 0){
//                    Toast.makeText(MainActivity.this, "拒绝地理位置权限将导致应用无法使用！", Toast.LENGTH_SHORT).show();
//                }
                break;
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case R.id.item_ble_start_scan:
                startBleScan();
                break;
            case R.id.item_ble_stop_scan:
                stopBleScan();
                break;
            case R.id.item_clear_rec_contents:
                receiveContents.clear();
                receiveAdapter.notifyDataSetChanged();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    private void startBleScan() {
        if(!checkScanable()) return;

        findViewById(R.id.layout_tips_bar).setVisibility(View.VISIBLE);
        currentBleScanListener = new BleScanCallback(MainActivity.this, bleDeviceAdapter);
        getBleScanner().startScan(currentBleScanListener);
        //开启一个线程，20s后自动关闭扫描
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(20000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        stopBleScan();
                    }
                });
            }
        }).start();
    }

    public void stopBleScan() {
        if(!checkScanable()) return;
        if(currentBleScanListener != null) getBleScanner().stopScan(currentBleScanListener);
        findViewById(R.id.layout_tips_bar).setVisibility(View.GONE);
    }

    private boolean checkScanable(){
        return bluetoothAdapter.getState() == BluetoothAdapter.STATE_ON;
    }

    private BluetoothLeScanner getBleScanner(){
        return bluetoothAdapter.getBluetoothLeScanner();
    }

}
