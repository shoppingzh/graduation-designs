package com.littlezheng.englishwriter.util;

import android.bluetooth.BluetoothDevice;

/**
 * Created by Administrator on 2018/3/14/014.
 */

public interface BleSearchListener {

    /**
     * 搜索到BLE蓝牙设备时的回调
     * @return 搜索到的BLE蓝牙设备
     */
    void onSearch(BluetoothDevice device);

}
