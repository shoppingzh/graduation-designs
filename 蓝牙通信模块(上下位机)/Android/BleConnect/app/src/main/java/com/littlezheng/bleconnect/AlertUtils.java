package com.littlezheng.bleconnect;

import android.app.AlertDialog;
import android.content.Context;

/**
 * Created by Administrator on 2017/10/2/002.
 */

public class AlertUtils {

    public static void alert(Context context, String message){
        AlertDialog alertDialog = new AlertDialog.Builder(context)
                .setMessage(message)
                .create();
        alertDialog.show();
    }

    public static void alert(Context context,String title, String message){
        AlertDialog alertDialog = new AlertDialog.Builder(context)
                .setTitle(title)
                .setMessage(message)
                .create();
        alertDialog.show();
    }

    public static AlertDialog alert(Context context, String message, boolean cancelable){
        AlertDialog alertDialog = new AlertDialog.Builder(context)
                .setMessage(message)
                .setCancelable(cancelable)
                .create();
        alertDialog.show();
        return alertDialog;
    }

    public static AlertDialog alert(Context context, String title, String message, boolean cancelable){
        AlertDialog alertDialog = new AlertDialog.Builder(context)
                .setTitle(title)
                .setMessage(message)
                .setCancelable(cancelable)
                .create();
        alertDialog.show();
        return alertDialog;
    }


}
