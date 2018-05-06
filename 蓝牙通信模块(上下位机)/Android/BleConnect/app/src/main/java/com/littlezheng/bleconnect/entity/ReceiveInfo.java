package com.littlezheng.bleconnect.entity;

/**
 * Created by Administrator on 2017/10/2/002.
 */

public class ReceiveInfo {

    private byte[] content;
    private long time;

    public ReceiveInfo(byte[] content, long time) {
        this.content = content;
        this.time = time;
    }

    public byte[] getContent() {
        return content;
    }

    public void setContent(byte[] content) {
        this.content = content;
    }

    public long getTime() {
        return time;
    }

    public void setTime(long time) {
        this.time = time;
    }
}
