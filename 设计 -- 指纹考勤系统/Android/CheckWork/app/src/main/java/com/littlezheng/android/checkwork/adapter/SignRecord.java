package com.littlezheng.android.checkwork.adapter;

import java.util.Date;

/**
 * Created by Administrator on 2018/4/21/021.
 */

public class SignRecord {

    private String name;
    private String department;
    private String phoneNum;
    private Date signTime;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public String getPhoneNum() {
        return phoneNum;
    }

    public void setPhoneNum(String phoneNum) {
        this.phoneNum = phoneNum;
    }

    public Date getSignTime() {
        return signTime;
    }

    public void setSignTime(Date signTime) {
        this.signTime = signTime;
    }

    @Override
    public String toString() {
        return "SignRecord{" +
                "name='" + name + '\'' +
                ", department='" + department + '\'' +
                ", phoneNum='" + phoneNum + '\'' +
                ", signTime=" + signTime +
                '}';
    }
}
