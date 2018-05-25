package com.littlezheng.android.checkwork.ble;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.util.Log;

/**
 * Created by Administrator on 2018/4/21/021.
 */

public class BleDeviceHolder {

    private static BleCommunicator bleCommunicator;
    private static final String TAG = "BleDeviceHolder";

    private Context mContext;
    private final String mDeviceName;
    private BluetoothDevice mDevice;

    public BleDeviceHolder(Context context, String deviceName) {
        if (deviceName == null) {
            throw new RuntimeException("deviceName为空!");
        }
        mDeviceName = deviceName;
        mContext = context;
    }

    /**
     * 搜索并连接蓝牙设备
     */
    public void scanConnect() {
        BluetoothAdapter bluetoothAdapter =
                ((BluetoothManager) mContext.getSystemService(Context.BLUETOOTH_SERVICE)).getAdapter();
        final BluetoothLeScanner scanner = bluetoothAdapter.getBluetoothLeScanner();
        ScanCallback callback = new ScanCallback() {
            @Override
            public void onScanResult(int callbackType, ScanResult result) {
                super.onScanResult(callbackType, result);
                Log.d(TAG, "发现蓝牙设备：" + result.getScanRecord().getDeviceName());
                if (mDeviceName.equals(result.getScanRecord().getDeviceName())) {
                    Log.d(TAG, mDeviceName + "已找到");
                    mDevice = result.getDevice();
                    //找到之后停止扫描
                    scanner.stopScan(this);
                    bleCommunicator = new SimpleBleCommunicator(mContext, mDevice);
                }
            }

        };
        //开始扫描
        scanner.startScan(callback);
    }

    /**
     * 获取得到的蓝牙设备
     *
     * @return
     */
    public BluetoothDevice getDevice() {
        return mDevice;
    }

    /**
     * 获取全局BLE通讯器
     *
     * @return
     */
    public static BleCommunicator getCommunicator() {
        return bleCommunicator;
    }

    interface Callback{

    }

}
