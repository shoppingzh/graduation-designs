package com.littlezheng.android.checkwork;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.JsonParseException;
import com.google.gson.reflect.TypeToken;
import com.littlezheng.android.checkwork.config.Urls;
import com.littlezheng.android.checkwork.model.Department;
import com.littlezheng.android.checkwork.net.AjaxResult;
import com.littlezheng.android.checkwork.net.NetUtils;
import com.littlezheng.android.checkwork.util.JsonUtils;

import java.io.IOException;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Response;

public class AddActivity extends AppCompatActivity {

    private static final String TAG = "AddActivity";

    private EditText nameEt;
    private EditText ageEt;
    private EditText phoneNumEt;
    private EditText emailEt;
    private Spinner departmentsSpn;
    private Button submitBtn;

    private List<Department> departments;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add);

        nameEt = (EditText) findViewById(R.id.et_name);
        ageEt = (EditText) findViewById(R.id.et_age);
        phoneNumEt = (EditText) findViewById(R.id.et_phone_num);
        emailEt = (EditText) findViewById(R.id.et_email);
        departmentsSpn = (Spinner) findViewById(R.id.spn_departments);
        submitBtn = (Button) findViewById(R.id.btn_submit_add);

        fillDepartments();

        submitBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                addEmployee();
            }
        });
    }

    //添加员工
    private void addEmployee() {
        String name = nameEt.getText().toString();
        if(name == null || name.trim().isEmpty()){
            Toast.makeText(AddActivity.this, "姓名为空！", Toast.LENGTH_SHORT).show();
            return;
        }

        String age = ageEt.getText().toString();
        String phoneNum = phoneNumEt.getText().toString();
        String email = emailEt.getText().toString();
        String departmentId = departments.get((int) departmentsSpn.getSelectedItemId()).getId().toString();
        String tempIdx = null;
        final Intent intent = getIntent();
        if(intent != null){
            tempIdx = String.valueOf(intent.getIntExtra("temp_idx", -1));
        }

        NetUtils.get(Urls.URL_API + getAddUri(name, age, phoneNum, email, departmentId, tempIdx), new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {

            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                String resp = response.body().string();
                Log.d(TAG, "响应：" + resp);
                Gson gson = new Gson();
                AjaxResult<Void> result = null;
                try{
                    result = gson.fromJson(resp, new TypeToken<AjaxResult<Void>>(){}.getType());
                }catch (JsonParseException e){
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(AddActivity.this, "添加失败！", Toast.LENGTH_SHORT).show();
                            Intent intent1 = new Intent(AddActivity.this, MainActivity.class);
                            startActivity(intent1);
                        }
                    });
                    return;
                }
                if(result != null){
                    if("0".equals(result.getCode())){
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(AddActivity.this, "添加成功！", Toast.LENGTH_SHORT).show();
                                Intent intent1 = new Intent(AddActivity.this, MainActivity.class);
                                startActivity(intent1);
                            }
                        });
                    }else{
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(AddActivity.this, "添加失败！", Toast.LENGTH_SHORT).show();
                                Intent intent1 = new Intent(AddActivity.this, MainActivity.class);
                                startActivity(intent1);
                            }
                        });
                    }
                }
            }
        });
    }

    //获取添加URI
    private String getAddUri(String name, String age, String phoneNum, String email,
                          String departmentId, String tempIdx) {
        StringBuilder sb = new StringBuilder("add_employee?");
        sb.append("name=").append(name).append("&");
        sb.append("age=").append(age).append("&");
        sb.append("phone_num=").append(phoneNum).append("&");
        sb.append("email=").append(email).append("&");
        sb.append("department_id=").append(departmentId).append("&");
        sb.append("temp_idx=").append(tempIdx);
        return sb.toString();
    }


    //联网获取部门数据并填充
    private void fillDepartments() {
        NetUtils.get(Urls.URL_GET_DEPARTMENTS, new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                String resp = response.body().string();
                Log.d(TAG, "响应：" + resp);
                Gson gson = new Gson();
                AjaxResult<List<Department>> result = null;

                try{
                    result = gson.fromJson(resp, new TypeToken<AjaxResult<List<Department>>>(){}.getType());
                }catch (JsonParseException e){
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            Toast.makeText(AddActivity.this, "部门信息获取失败！", Toast.LENGTH_SHORT);
                        }
                    });
                    return;
                }

                if(result != null){
                    if("0".equals(result.getCode())){
                        departments = result.getData();
                        final String[] names = new String[departments.size()];
                        int i = 0;
                        for(Department d : result.getData()){
                            names[i++] = d.getName();
                        }

                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                departmentsSpn.setAdapter(new ArrayAdapter(AddActivity.this,
                                        android.R.layout.simple_spinner_dropdown_item, names));
                                submitBtn.setEnabled(true);
                            }
                        });
                    }else{
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(AddActivity.this, "部门信息获取失败！", Toast.LENGTH_SHORT);
                            }
                        });
                    }
                }
            }
        });
    }


}
