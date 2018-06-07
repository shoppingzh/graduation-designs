package com.littlezheng.englishwriter.util;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.util.Log;
import android.widget.Toast;

import com.littlezheng.englishwriter.MainActivity;

import java.util.Arrays;

/**
 * Created by Administrator on 2018/3/14/014.
 */

public final class BleUtils {

    private static final String TAG = "BleUtils";

    /**
     * 搜索设备
     *
     * @param btAdapter         蓝牙适配器
     * @param bleSearchListener 搜索监听器
     */
    public static void searchDevice(BluetoothAdapter btAdapter,
                                    final BleSearchListener bleSearchListener) {
        btAdapter.getBluetoothLeScanner().startScan(new ScanCallback() {
            @Override
            public void onScanResult(int callbackType, ScanResult result) {
                super.onScanResult(callbackType, result);
                BluetoothDevice device = result.getDevice();
                Log.d(TAG, "找到设备：[" + device.getName() + ", " + device.getAddress() + "]");
                bleSearchListener.onSearch(device);
            }
        });
    }

    /**
     * 搜索指定设备
     *
     * @param btAdapter         蓝牙适配器
     * @param deviceName        设备名称
     * @param bleSearchListener 搜索监听器
     */
    public static void searchDevice(BluetoothAdapter btAdapter, final String deviceName,
                                    final BleSearchListener bleSearchListener) {
        btAdapter.getBluetoothLeScanner().startScan(new ScanCallback() {
            @Override
            public void onScanResult(int callbackType, ScanResult result) {
                super.onScanResult(callbackType, result);
                BluetoothDevice device = result.getDevice();
                if (deviceName.equals(device.getName())) {
                    Log.d(TAG, "找到设备：[" + device.getName() + ", " + device.getAddress() + "]");
                    bleSearchListener.onSearch(device);
                }

            }
        });
    }

    /**
     * 发送数据到BLE设备
     *
     * @param gatt
     * @param characteristic
     * @param bytes          发送的数据
     */
    public static void send(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic,
                            byte... bytes) {
        if (gatt == null || characteristic == null || bytes == null)
            return;
        gatt.setCharacteristicNotification(characteristic, true);
        characteristic.setValue(bytes);
        gatt.writeCharacteristic(characteristic);
    }


}
