package com.littlezheng.englishwriter;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.littlezheng.englishwriter.util.BleConnector;
import com.littlezheng.englishwriter.util.BleSearchListener;
import com.littlezheng.englishwriter.util.BleUtils;

import java.util.Arrays;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    private static final char LETTERS[] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
            'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
            'U', 'V', 'W', 'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
            'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
            'u', 'v', 'w', 'x', 'y', 'z'
    };
    private static final String LETTER_HEX[] = {
            "41", "43", "43", "44", "45", "46", "47", "48", "49", "4a",
            "4b", "4c", "4d", "4e", "4f", "50", "51", "52", "53", "54",
            "55", "56", "57", "58", "59", "5a",
            "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a",
            "6b", "6c", "6d", "6e", "6f", "70", "71", "72", "73", "74",
            "75", "76", "77", "78", "79", "7a",
    };

    private BluetoothGatt mGatt;
    private BluetoothGattCharacteristic mCharacteristic;

    private TextView englishTv;
    private EditText inputEt;
    private Button sendBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        englishTv = (TextView) findViewById(R.id.tv_english);
        inputEt = (EditText) findViewById(R.id.et_input);
        sendBtn = (Button) findViewById(R.id.btn_send);

        inputEt.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                if(s.length() > 1){
                    inputEt.setText("");
                    Toast.makeText(MainActivity.this, "只能输入一个字符！", Toast.LENGTH_SHORT).show();
                    return;
                }
            }

            @Override
            public void afterTextChanged(Editable s) {

            }
        });

        sendBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //获取输入的字符
                String str = inputEt.getText().toString();
                char ch = str.charAt(0);
                englishTv.setText(String.valueOf(ch));
                if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
                    BleUtils.send(mGatt, mCharacteristic, (byte)ch);
            }
        });

        //地理位置授权
        if(ActivityCompat.checkSelfPermission(MainActivity.this,
                Manifest.permission.ACCESS_FINE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, 1);
        }
        if(ActivityCompat.checkSelfPermission(MainActivity.this,
                Manifest.permission.ACCESS_COARSE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, 2);
        }

        BleConnector bleConnector = new BleConnector(this);
        bleConnector.setConnectListener(new BleConnector.BleConnectListener() {
            @Override
            public void onConnected(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
                mGatt = gatt;
                mCharacteristic = characteristic;
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this, "蓝牙连接成功！", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
        bleConnector.setReadListener(new BleConnector.ReadListener() {
            @Override
            public void onRead(byte[] value) {

            }
        });
        bleConnector.connect("BT05");


    }
}
