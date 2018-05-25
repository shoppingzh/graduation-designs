package com.littlezheng.android.checkwork.adapter;

import android.content.Context;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.littlezheng.android.checkwork.R;

import org.w3c.dom.Text;

import java.text.SimpleDateFormat;
import java.util.List;

/**
 * Created by Administrator on 2018/4/21/021.
 */

public class SignRecordAdapter extends ArrayAdapter<SignRecord> {

    private Context mContext;
    private int mResource;
    private List<SignRecord> mList;

    public SignRecordAdapter(@NonNull Context context, @LayoutRes int resource,
                             @NonNull List<SignRecord> objects) {
        super(context, resource, objects);
        mContext = context;
        mResource = resource;
        mList = objects;
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        ViewHolder viewHolder = null;
        if(convertView == null){
            convertView = LayoutInflater.from(mContext).inflate(mResource, parent, false);
            viewHolder = new ViewHolder();
            viewHolder.nameTv = convertView.findViewById(R.id.tv_name);
            viewHolder.departmentTv = convertView.findViewById(R.id.tv_department);
            viewHolder.phoneNumTv = convertView.findViewById(R.id.tv_phone_num);
            viewHolder.timeTv = convertView.findViewById(R.id.tv_sign_time);
            convertView.setTag(viewHolder);
        }else{
            viewHolder = (ViewHolder) convertView.getTag();
        }

        SignRecord signRecord = getItem(position);
        viewHolder.nameTv.setText(signRecord.getName());
        viewHolder.departmentTv.setText(signRecord.getDepartment());
        viewHolder.phoneNumTv.setText(signRecord.getPhoneNum());
        viewHolder.timeTv.setText(new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(signRecord.getSignTime()));
        return convertView;
    }

    private class ViewHolder{
        TextView nameTv;
        TextView departmentTv;
        TextView phoneNumTv;
        TextView timeTv;
    }

}
