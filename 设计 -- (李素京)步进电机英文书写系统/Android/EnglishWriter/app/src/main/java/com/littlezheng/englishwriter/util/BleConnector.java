package com.littlezheng.englishwriter.util;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.util.Log;
import android.widget.Toast;

import com.littlezheng.englishwriter.MainActivity;

import java.util.Arrays;
import java.util.UUID;

/**
 * Created by Administrator on 2018/4/1/001.
 */

public class BleConnector {

    private static final UUID SERVICE_UUID = UUID.fromString("0000ffe0-0000-1000-8000-00805f9b34fb");
    private static final UUID CHARACTERISTIC_UUID = UUID.fromString("0000ffe1-0000-1000-8000-00805f9b34fb");
    private static final String TAG = "BleConnector";

    private Context mContext;
    private BluetoothAdapter mBluetoothAdapter;

    private BluetoothGatt mGatt;
    private BluetoothGattCharacteristic mCharacteristic;
    private boolean connected;

    private BleConnectListener connectListener;
    private ReadListener readListener;

    public BleConnector(Context context) {
        mContext = context;
        mBluetoothAdapter = ((BluetoothManager) context.getSystemService(Context.BLUETOOTH_SERVICE)).getAdapter();
    }

    /**
     * 连接BLE设备
     *
     * @param deviceName BLE设备名称
     */
    public void connect(String deviceName) {
        openBluetoothIfClosed();
        BleUtils.searchDevice(mBluetoothAdapter, deviceName, new BleSearchListener() {
            @Override
            public void onSearch(BluetoothDevice device) {
                device.connectGatt(mContext, true, new BluetoothGattCallback() {
                    @Override
                    public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
                        super.onConnectionStateChange(gatt, status, newState);
                        //连接成功
                        if (status == BluetoothGatt.GATT_SUCCESS
                                && newState == BluetoothProfile.STATE_CONNECTED) {
                            connected = true;
                            //搜索服务
                            gatt.discoverServices();
                        }
                    }

                    @Override
                    public void onServicesDiscovered(BluetoothGatt gatt, int status) {
                        super.onServicesDiscovered(gatt, status);
                        mGatt = gatt;
                        BluetoothGattService service = gatt.getService(SERVICE_UUID);
                        BluetoothGattCharacteristic characteristic =
                                service.getCharacteristic(CHARACTERISTIC_UUID);
                        if (characteristic != null) {
                            mCharacteristic = characteristic;
                            if (connectListener != null)
                                connectListener.onConnected(gatt, characteristic);
                        }

                    }

                    @Override
                    public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
                        super.onCharacteristicWrite(gatt, characteristic, status);
                        Log.d(TAG, gatt.getDevice().getName() + "写入数据：" + Arrays.toString(characteristic.getValue()));
                    }

                    @Override
                    public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                        super.onCharacteristicChanged(gatt, characteristic);
                        if (readListener != null)
                            readListener.onRead(characteristic.getValue());
                    }
                });
            }
        });
    }

    /**
     * 开启蓝牙
     */
    private void openBluetoothIfClosed() {
        if (!mBluetoothAdapter.isEnabled())
            mBluetoothAdapter.enable();
    }

    public BleConnectListener getConnectListener() {
        return connectListener;
    }

    public void setConnectListener(BleConnectListener connectListener) {
        this.connectListener = connectListener;
    }

    public ReadListener getReadListener() {
        return readListener;
    }

    public void setReadListener(ReadListener readListener) {
        this.readListener = readListener;
    }

    public boolean isConnected() {
        return connected;
    }

    public interface BleConnectListener {
        void onConnected(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic);
    }

    public interface ReadListener {
        void onRead(byte[] value);
    }

}
