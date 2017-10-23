package com.sinosoft.autotest.constant;

/**
 * Element Type枚举(请传递下列括号中的字符串)<br>
 *  ID("id"), TAG_NAME("tag_name"), NAME("name"), CLASS_NAME("class_name"), XPATH("xpath"),
 *  CSS_SELECTOR("css_selector"), LINK_TEXT("link_text"), PARTIAL_LINK_TEXT("partial_link_text");
 */
public enum ElementTypeEnum{
    ID("id"), TAG_NAME("tag_name"), NAME("name"), CLASS_NAME("class_name"), XPATH("xpath"),
    CSS_SELECTOR("css_selector"), LINK_TEXT("link_text"), PARTIAL_LINK_TEXT("partial_link_text");

    private String elementType;
    ElementTypeEnum(String elementType){
        this.elementType = elementType;
    }

    public String getElementType(){
        return elementType;
    }
}