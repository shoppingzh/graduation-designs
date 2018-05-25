package com.littlezheng.android.checkwork.util;

import android.support.annotation.Nullable;

import com.google.gson.Gson;
import com.google.gson.JsonParseException;
import com.google.gson.JsonParser;
import com.google.gson.JsonSyntaxException;
import com.google.gson.reflect.TypeToken;
import com.littlezheng.android.checkwork.json.ParameterizedTypeImpl;

/**
 * Created by Administrator on 2018/2/1/001.
 */

public class JsonUtils {

    /**
     * 判断给定的字符串是否为json字符串
     *
     * @param json 字符串
     * @return
     */
    public static boolean isCorrectJson(String json) {
        try {
            new JsonParser().parse(json);
            return true;
        } catch (JsonParseException e) {
            e.printStackTrace();
            return false;
        }
    }

    /**
     * 将json字符串转为对象
     *
     * @param json  json字符串
     * @param clazz 对象所属类
     * @param <T>
     * @return 转换后的对象
     */
    @Nullable
    public static <T> T fromJson(String json, Class<T> clazz) {
        if (!isCorrectJson(json))
            return null;
        Gson gson = new Gson();
        T t = null;
        try {
            t = gson.fromJson(json, clazz);
        } catch (JsonSyntaxException e) {
            e.printStackTrace();
        }
        return t;
    }

    /**
     * 将一个对象转化为json字符串
     *
     * @param obj 对象
     * @return
     */
    public static String toJson(Object obj) {
        Gson gson = new Gson();
        return gson.toJson(obj);
    }

}
