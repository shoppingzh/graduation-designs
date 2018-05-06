package com.littlezheng.bleconnect;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.os.Build;
import android.support.annotation.RequiresApi;

import com.littlezheng.bleconnect.Adapter.BleDeviceAdapter;

import java.util.List;

/**
 * Created by Administrator on 2017/10/1/001.
 */

@RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
public class BleScanCallback extends ScanCallback {

    private Context mContext;
    private BleDeviceAdapter mAdapter;

    public BleScanCallback(Context context, BleDeviceAdapter adapter) {
        mContext = context;
        mAdapter = adapter;
        adapter.clear();
    }

    @Override
    public void onScanResult(int callbackType, ScanResult result) {
        super.onScanResult(callbackType, result);
        BluetoothDevice device = result.getDevice();
        List<BluetoothDevice> devices = mAdapter.getDevices();
        if(!devices.contains(device)){
            devices.add(device);
            mAdapter.notifyDataSetChanged();
        }
    }

    @Override
    public void onScanFailed(int errorCode) {
        super.onScanFailed(errorCode);
    }

}
