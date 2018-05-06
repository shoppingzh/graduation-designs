package com.littlezheng.android.checkwork.net;

/**
 * Created by Administrator on 2018/4/20/020.
 */

public class AjaxResult<T> {

    private String code;
    private String message;
    private T data;

    public AjaxResult(String code) {
        this.code = code;
    }

    public AjaxResult(String code, T data) {
        this.code = code;
        this.data = data;
    }

    public AjaxResult(String code, String message, T data) {
        this.code = code;
        this.message = message;
        this.data = data;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "AjaxResult{" +
                "code='" + code + '\'' +
                ", message='" + message + '\'' +
                ", data=" + data +
                '}';
    }
}
