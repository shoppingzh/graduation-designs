package com.littlezheng.android.checkwork.ble;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.util.Log;

import java.util.Arrays;
import java.util.UUID;

/**
 * Created by Administrator on 2018/4/20/020.
 */

public class SimpleBleCommunicator extends BleCommunicator {

    private static final String TAG = "SimpleBleCommunicator";

    //00001800
    //0000ffe0
    private static final UUID SERVICE_UUID = UUID.fromString("0000ffe0-0000-1000-8000-00805f9b34fb");
    private static final UUID CHARACTERISTIC_UUID = UUID.fromString("0000ffe1-0000-1000-8000-00805f9b34fb");

    private Context mContext;
    private final BluetoothDevice mDevice;
    private BluetoothGatt mGatt;
    private BluetoothGattCharacteristic mCharacteristic;

    SimpleBleCommunicator(Context context, BluetoothDevice device){
        mContext = context;
        mDevice = device;
        connect();
    }

    //连接BLE设备
    private void connect(){
        mDevice.connectGatt(mContext, true, new BluetoothGattCallback() {
            @Override
            public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
                super.onConnectionStateChange(gatt, status, newState);
                //连接成功
                if (status == BluetoothGatt.GATT_SUCCESS
                        && newState == BluetoothProfile.STATE_CONNECTED) {
                    Log.d(TAG, "已连接");
                    //搜索服务
                    gatt.discoverServices();
                }
            }

            @Override
            public void onServicesDiscovered(BluetoothGatt gatt, int status) {
                super.onServicesDiscovered(gatt, status);
                BluetoothGattService service = gatt.getService(SERVICE_UUID);
                if(service != null){
                    BluetoothGattCharacteristic characteristic =
                            service.getCharacteristic(CHARACTERISTIC_UUID);
                    if (characteristic != null) {
                        Log.d(TAG, "信道以找到，准备就绪..");
                        mGatt = gatt;
                        mCharacteristic = characteristic;
                        mGatt.setCharacteristicNotification(mCharacteristic, true);
                    }
                }
            }

            @Override
            public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
                super.onCharacteristicWrite(gatt, characteristic, status);
                Log.d(TAG, gatt.getDevice().getName() + "发送数据：" + Arrays.toString(characteristic.getValue()));
            }

            @Override
            public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                super.onCharacteristicChanged(gatt, characteristic);
                Log.d(TAG, gatt.getDevice().getName() + "接收数据：" + Arrays.toString(characteristic.getValue()));
                mListener.onReceive(characteristic.getValue());
            }

            @Override
            public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
                super.onCharacteristicRead(gatt, characteristic, status);
                Log.d(TAG, gatt.getDevice().getName() + "读取到数据：" + Arrays.toString(characteristic.getValue()));
            }
        });
    }


    @Override
    public void send(final byte[] data) {
        if(data == null)
            return;
        if(mGatt != null){
            mCharacteristic.setValue(data);
            mGatt.writeCharacteristic(mCharacteristic);
        }
    }




}
