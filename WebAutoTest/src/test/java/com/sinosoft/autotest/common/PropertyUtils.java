package com.sinosoft.autotest.common;

import java.io.IOException;
import java.util.Properties;

/**
 * 读取配置文件
 * Created by Administrator on 2016/11/23.
 */
public class PropertyUtils {

    public static Properties   readProperties() {
        Properties properties = new Properties();
        try {
            properties.load(PropertyUtils.class.getResourceAsStream("/config.properties"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return properties;
    }
}
