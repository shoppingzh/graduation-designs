package com.littlezheng.bleconnect.Adapter;

import android.content.Context;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.littlezheng.bleconnect.AlertUtils;
import com.littlezheng.bleconnect.R;
import com.littlezheng.bleconnect.entity.ReceiveInfo;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

/**
 * Created by Administrator on 2017/10/2/002.
 */

public class BleReceiveAdapter extends ArrayAdapter<ReceiveInfo> {

    private Context mContext;
    private int mResource;
    private List<ReceiveInfo> contents;

    public BleReceiveAdapter(@NonNull Context context, @LayoutRes int resource, @NonNull List<ReceiveInfo> objects) {
        super(context, resource, objects);
        mContext = context;
        mResource = resource;
        contents = objects;
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        final ViewHolder viewHolder;
        if(convertView == null){
            convertView = LayoutInflater.from(mContext).inflate(mResource, parent, false);
            viewHolder = new ViewHolder();
            viewHolder.receiveContentTv = (TextView) convertView.findViewById(R.id.tv_receive_content);
            viewHolder.currTimeTv = (TextView) convertView.findViewById(R.id.tv_curr_time);
            convertView.setTag(viewHolder);
        }else{
            viewHolder = (ViewHolder) convertView.getTag();
        }

        final ReceiveInfo info = getItem(position);
        viewHolder.receiveContentTv.setText(Arrays.toString(info.getContent()));
        viewHolder.currTimeTv.setText(getCurrTime(info.getTime()));
        convertView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertUtils.alert(mContext, new String(info.getContent()));
            }
        });

        return convertView;
    }

    public String getCurrTime(long time) {
        DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return df.format(new Date(time));
    }

    private class ViewHolder{
        TextView receiveContentTv;
        TextView currTimeTv;
    }

}
