package com.sinosoft.autotest.constant;

/**
 * 基础组件枚举(请传递下列括号中的字符串)<br>
 * CHROME("chrome"), FIREFOX("firefox"), CLOUD_PLATFORM("clloudplatform"),PALACE("palace")
 */
public enum BasicComponentEnum {

    CHROME("chrome"), FIREFOX("firefox"), IE("ie"), CLOUD_PLATFORM("clloudplatform"), PALACE("palace"),
    DEFAULT_PRE_DELAY_TIME("defaultPreDelayTime"), DEFAULT_POST_DELAY_TIME("defaultPostDelayTime"),
    INVOKE_METHOD_RETRY_TIMES("invokeMethodRetryTimes"), TRUE("true"), FALSE("false"),
    IMPLICITLY_WAIT_TIMEOUT("implicitlyWaitTimeOut"), MINUS_SIGN("-"),
    SEARCH_ELEMENT_RETRY_TIMES("searchElementRetryTimes"), WEB_DRIVER_PATH("webDriverPath"),
    IE_WEB_DRIVER_PATH("IEWebDriverPath");

    private String info;
    BasicComponentEnum(String info){
        this.info = info;
    }

    public String getBasicComponentInfo(){
        return info;
    }
}
