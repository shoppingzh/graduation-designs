package com.littlezheng.bleconnect;

import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;

/**
 * Created by Administrator on 2017/10/2/002.
 */

public interface BleListener {

    void onConnected(BluetoothGatt gatt);

    void onDisconnected(BluetoothGatt gatt);

    void onCharacteristicGot(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic);

    void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic);

    void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic);

}
