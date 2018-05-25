package com.littlezheng.android.checkwork.ble;

/**
 * Created by Administrator on 2018/4/20/020.
 */

public abstract class BleCommunicator {

    public abstract void send(byte[] data);

    static OnReceiveListener mListener = new OnReceiveListener() {
        @Override
        public void onReceive(byte[] data) {
            //do nothing
        }
    };

    public static void setOnReceiveListener(OnReceiveListener listener) {
        mListener = listener;
    }

    public interface OnReceiveListener{
        void onReceive(byte[] data);
    }

}
