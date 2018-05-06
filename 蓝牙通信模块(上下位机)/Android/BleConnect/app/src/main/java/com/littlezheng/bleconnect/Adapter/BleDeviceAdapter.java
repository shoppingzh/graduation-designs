package com.littlezheng.bleconnect.Adapter;

import android.app.Activity;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.graphics.Color;
import android.os.Build;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.annotation.RequiresApi;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.littlezheng.bleconnect.BleListener;
import com.littlezheng.bleconnect.MainActivity;
import com.littlezheng.bleconnect.R;

import java.util.Arrays;
import java.util.List;
import java.util.UUID;

/**
 * Created by Administrator on 2017/10/1/001.
 */

public class BleDeviceAdapter extends ArrayAdapter<BluetoothDevice> {

    private static final String TAG = "BleDeviceAdapter";

    private static final UUID SERVICE_UUID = UUID.fromString("0000ffe0-0000-1000-8000-00805f9b34fb");
    private static final UUID CHARACTERISTIC_UUID = UUID.fromString("0000ffe1-0000-1000-8000-00805f9b34fb");

    private Context mContext;
    private int mResource;
    private List<BluetoothDevice> mDevices;
    private BleListener bleListener;

    //连接设备
    private int connects;

    public BleDeviceAdapter(@NonNull Context context, @LayoutRes int resource, @NonNull List<BluetoothDevice> devices) {
        super(context, resource, devices);
        mContext = context;
        mResource = resource;
        mDevices = devices;
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {

        final ViewHolder viewHolder;
        if(convertView == null){
            convertView = LayoutInflater.from(mContext).inflate(mResource, parent, false);
            viewHolder = new ViewHolder();
            viewHolder.nameTv = (TextView) convertView.findViewById(R.id.tv_ble_device_name);
            viewHolder.disconnectBtn = (Button) convertView.findViewById(R.id.btn_disconnect);
            convertView.setTag(viewHolder);
        }else{
            viewHolder = (ViewHolder) convertView.getTag();
        }

        final BluetoothDevice device = getItem(position);
        viewHolder.nameTv.setText(device.getName()+"("+device.getAddress()+")");
        viewHolder.nameTv.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR2)
            @Override
            public void onClick(View v) {
//                Toast.makeText(mContext, "设备："+device.getName(), Toast.LENGTH_SHORT).show();
                ((MainActivity)mContext).stopBleScan();
                BluetoothGatt gatt = device.connectGatt(mContext, false, new BluetoothGattCallback() {
                    @Override
                    public void onConnectionStateChange(final BluetoothGatt gatt, int status, int newState) {
                        super.onConnectionStateChange(gatt, status, newState);
                        viewHolder.disconnectBtn.setOnClickListener(new View.OnClickListener() {
                            @Override
                            public void onClick(View v) {
                                gatt.disconnect();
                            }
                        });

                        //连接
                        if(status == BluetoothGatt.GATT_SUCCESS && newState == BluetoothProfile.STATE_CONNECTED){
                            if(connects >= 1) return;
                            connects++;

                            //连接成功马上搜索服务
                            gatt.discoverServices();
                            ((Activity)mContext).runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    viewHolder.nameTv.setTextColor(Color.RED);
                                    viewHolder.disconnectBtn.setVisibility(View.VISIBLE);
                                    Toast.makeText(mContext, device.getName()+"连接成功！", Toast.LENGTH_SHORT).show();
                                }
                            });
                            if(bleListener != null) bleListener.onConnected(gatt);
                        }

                        //断开
                        if(status == BluetoothGatt.GATT_SUCCESS && newState == BluetoothProfile.STATE_DISCONNECTED){
                            connects--;
                            ((Activity)mContext).runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    viewHolder.nameTv.setTextColor(Color.BLACK);
                                    viewHolder.disconnectBtn.setVisibility(View.GONE);
                                    Toast.makeText(mContext, device.getName()+"已断开连接！", Toast.LENGTH_SHORT).show();
                                }
                            });
                            if(bleListener != null) bleListener.onDisconnected(gatt);
                        }
                    }

                    @Override
                    public void onServicesDiscovered(BluetoothGatt gatt, int status) {
                        super.onServicesDiscovered(gatt, status);
                        Log.d(TAG, "发现服务");
                        BluetoothGattService service = gatt.getService(SERVICE_UUID);
                        BluetoothGattCharacteristic characteristic = service.getCharacteristic(CHARACTERISTIC_UUID);
                        if(bleListener != null) bleListener.onCharacteristicGot(gatt, characteristic);
                    }

                    @Override
                    public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
                        super.onCharacteristicRead(gatt, characteristic, status);
                    }

                    @Override
                    public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
                        super.onCharacteristicWrite(gatt, characteristic, status);
                        Log.d(TAG,gatt.getDevice().getName()+"写入数据：" + Arrays.toString(characteristic.getValue()));
                        if(bleListener != null) bleListener.onCharacteristicWrite(gatt, characteristic);
                    }

                    @Override
                    public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                        super.onCharacteristicChanged(gatt, characteristic);
                        Log.d(TAG, "收到数据："+ Arrays.toString(characteristic.getValue()));
                        if(bleListener != null) bleListener.onCharacteristicRead(gatt, characteristic);
                    }
                });
            }
        });

        return convertView;
    }

    public List<BluetoothDevice> getDevices() {
        return mDevices;
    }

    public void setBleListener(BleListener bleListener) {
        this.bleListener = bleListener;
    }

    private class ViewHolder{
        TextView nameTv;
        Button disconnectBtn;
    }



}
