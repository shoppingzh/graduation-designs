package com.littlezheng.smarthome.ble;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.util.Log;

import java.util.Arrays;
import java.util.List;
import java.util.UUID;

/**
 * Created by Administrator on 2018/5/22/022.
 */

public class BleTool {

    private static final String TAG = "BleTool";
    private static BluetoothGatt bluetoothGatt;
    private static BluetoothGattCharacteristic characteristic;
    private static OnReceiveListener onReceiveListener;

    /**
     * 连接一个BLE设备
     *
     * @param device          BLE设备
     * @param context
     * @param connectCallback 连接回调
     */
    public static void connectDevice(BluetoothDevice device, Context context,
                                     final ConnectCallback connectCallback) {
        device.connectGatt(context, false, new BluetoothGattCallback() {
            @Override
            public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
                super.onConnectionStateChange(gatt, status, newState);
                if (status == BluetoothGatt.GATT_SUCCESS &&
                        newState == BluetoothProfile.STATE_CONNECTED) {
                    Log.d(TAG, gatt.getDevice().getName() + "连接成功");
                    connectCallback.onConnect(gatt);
                    gatt.discoverServices();
                }
            }

            @Override
            public void onServicesDiscovered(BluetoothGatt gatt, int status) {
                super.onServicesDiscovered(gatt, status);
                if (status == BluetoothGatt.GATT_SUCCESS) {
                    bluetoothGatt = gatt;
                    connectCallback.onServicesDiscovered(gatt.getServices());
                }
            }

            @Override
            public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
                super.onCharacteristicWrite(gatt, characteristic, status);
                Log.d(TAG, "发送数据：" + Arrays.toString(characteristic.getValue()));
            }

            @Override
            public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                super.onCharacteristicChanged(gatt, characteristic);
                byte[] data = characteristic.getValue();
                Log.d(TAG, "接收数据：" + Arrays.toString(data));
                if (onReceiveListener != null) {
                    onReceiveListener.onReceive(data);
                }
            }
        });
    }

    /**
     * 关闭当前连接
     */
    public static void disconnect(){
        bluetoothGatt.disconnect();
    }

    /**
     * 选择通信通道
     *
     * @param serviceUuidStr        服务UUID
     * @param characteristicUuidStr 信道UUID
     */
    public static void chooseChannel(String serviceUuidStr, String characteristicUuidStr) {
        if (bluetoothGatt == null) {
            return;
        }

        UUID serviceUuid = UUID.fromString(serviceUuidStr);
        UUID characteristicUuid = UUID.fromString(characteristicUuidStr);
        BluetoothGattService service = bluetoothGatt.getService(serviceUuid);
        if (service == null) {
            throw new RuntimeException("不存在的服务！");
        }

        characteristic = service.getCharacteristic(characteristicUuid);
        if (characteristic == null) {
            throw new RuntimeException("不存在该通信通道！");
        }

        bluetoothGatt.setCharacteristicNotification(characteristic, true);
    }

    /**
     * 发送数据
     *
     * @param data 发送的数据
     */
    public static void send(byte[] data) {
        if (bluetoothGatt != null && characteristic != null) {
            characteristic.setValue(data);
            bluetoothGatt.writeCharacteristic(characteristic);
        }
    }

    public static void setOnReceiveListener(OnReceiveListener listener) {
        onReceiveListener = listener;
    }


    //连接回调
    public interface ConnectCallback {
        /**
         * 连接回调，该回调在其它线程中，UI更新请在主线程进行
         *
         * @param gatt
         */
        void onConnect(BluetoothGatt gatt);

        /**
         * 发现服务回调，该回调在其它线程中，UI更新请在主线程进行
         *
         * @param services 发现的服务
         */
        void onServicesDiscovered(List<BluetoothGattService> services);

    }

    //接收监听器
    public interface OnReceiveListener {
        void onReceive(byte[] data);
    }

}
