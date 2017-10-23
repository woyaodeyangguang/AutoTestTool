package com.sinosoft.autotest.constant;

/**
 * 表单中各个组件类型(请传递下列括号中的字符串)<br>
 * TABLE("table"), TEXT("text"), SELECT("select"), TYPE("type"), OPTION("option"), VALUE("value"),
 * CLASS("class"), TR("tr"), TD("td"), TH("th")
 */
public enum FormComponentTypeEnum{
    TABLE("table"), TEXT("text"), SELECT("select"), TYPE("type"), OPTION("option"), VALUE("value"),
     CLASS("class"), TR("tr"), TD("td"), TH("th"), CHECKBOX_TRUE_FULL("checkbox_true_full"),
     INPUT("input");

    private String componetType;
    FormComponentTypeEnum(String componetType){
        this.componetType = componetType;
    }

    public String getComponentType(){
        return componetType;
    }
}

