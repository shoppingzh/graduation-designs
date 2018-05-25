package com.littlezheng.android.checkwork.net;

import android.util.Log;

import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;

/**
 * Created by Administrator on 2018/4/20/020.
 */

public class NetUtils {

    private static final String TAG = "NetUtils";

    /**
     * get请求
     *
     * @param url      请求url
     * @param callback 回调
     */
    public static void get(String url, Callback callback) {
        Log.d(TAG, "发送get请求: [" + url + "]");
        OkHttpClient client = new OkHttpClient();
        final Request request = new Request.Builder()
                .url(url)
                .get()
                .build();
        client.newCall(request).enqueue(callback);
    }

}
