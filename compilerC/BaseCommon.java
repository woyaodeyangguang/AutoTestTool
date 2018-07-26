package com.sinosoft.selenium;

import org.apache.commons.lang3.StringUtils;
import org.openqa.selenium.By;
import org.openqa.selenium.Keys;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.support.ui.WebDriverWait;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.TimeUnit;

import static com.sinosoft.selenium.constant.ElementTypeEnum.*;
import static com.sinosoft.selenium.constant.FormComponentTypeEnum.*;
import static com.sinosoft.selenium.constant.BasicComponentEnum.*;


/**
 * Created by Administrator on 2016/9/8.
 */
public class BaseCommon {
    private final String SEND_KEYS_METHOD = "sendKeys";
    private final String CLEAR_METHOD ="clear";
    private final String CLICK_METHOD = "click";

    // 延迟时间
    private  long defaultPreDelayTime = 400;
    private  long defaultPostDelayTime = 1600;

    // 基础组件
    private static WebDriver driver;

    public WebDriver getDriver() {
        return driver;
    }

    public void setDriver(WebDriver driver) {
        BaseCommon.driver = driver;
    }

    private static WebDriverWait wait;

    /**
     * 初始化基础组件
     */
     BaseCommon(String browserType) {
         if(StringUtils.equalsIgnoreCase(CHROME.getBasicComponentInfo(), browserType)){
             System.setProperty("webdriver.chrome.driver"
                     , "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chromedriver.exe");
             driver = new ChromeDriver();
         }else  if(StringUtils.equalsIgnoreCase(FIREFOX.getBasicComponentInfo(), browserType)) {
             driver = new FirefoxDriver();
         }else {
             throw new RuntimeException("init base component fail, can't match browser type!");
         }
        driver.manage().window().maximize();
        driver.manage().timeouts().implicitlyWait(10, TimeUnit.SECONDS);
        wait = new WebDriverWait(driver, 20);
    }

    /**
     * 默认初始化Chrome浏览器组件
     */
    BaseCommon(){
        this(CHROME.getBasicComponentInfo());
    }

    /**
     * 修改执行动作的延迟时间.
     */
    public void initDelayTime(long preDelayTime, long postDelayTime) {
        defaultPreDelayTime = preDelayTime;
        defaultPostDelayTime = postDelayTime;
    }

    /**
     * 延迟执行driver中方法
     * @param object
     * @param methodName
     * @param args
     */
    public  void invokeMethod(Object object, String methodName, String... args) {
        if (StringUtils.isEmpty(methodName) || object == null) {
            return;
        }
        try {
            Class[] parameterTypes = new Class[args.length];
            for (int i = 0; i < args.length ; i++) {
                if (args[i].getClass() == String.class && SEND_KEYS_METHOD.equals(methodName)) {
                    ((WebElement)object).sendKeys(args);
                    return;
                } else {
                    parameterTypes[i]= args[i].getClass();
                }
            }

            Class clazz = object.getClass();
            Method method = clazz.getMethod(methodName, parameterTypes);
            Thread.currentThread().sleep(defaultPreDelayTime);
            Object result = method.invoke(object, args);
            Thread.currentThread().sleep(defaultPostDelayTime);
        } catch (Exception e) {
            System.out.println("----------------invokeMethod fail----------------");
            e.printStackTrace();
        }

    }

    /**
     * 登录系统
     * @param url The url which The WebDriver will to open.
     * @param inputUsernameId The username input id.
     * @param username The login username.
     * @param selectRoleId The select role id.
     * @param inputPasswordId The password input id.
     * @param password The login password.
     * @param  submitBtnId The submit button id.
     */
    public void login(String url, String inputUsernameId, String username, String selectRoleId,
                      String inputPasswordId, String password,
                      String submitBtnId, String... selectRoleType) {
        driver.get(url);
        invokeMethod(driver.findElement(By.id(inputUsernameId)), CLEAR_METHOD);
        invokeMethod(driver.findElement(By.id(inputUsernameId)), SEND_KEYS_METHOD, username);
        driver.findElement(By.id(inputUsernameId)).sendKeys(Keys.TAB);
        try{
            Thread.currentThread().sleep(800);
        }catch(Exception e){
        }

        if(selectRoleType != null && selectRoleType.length ==1){
            invokeMethod(driver.findElement(By.id(selectRoleId)), SEND_KEYS_METHOD,
                    selectRoleType[0]);
        }
        invokeMethod(driver.findElement(By.id(inputPasswordId)), CLEAR_METHOD);
        invokeMethod(driver.findElement(By.id(inputPasswordId)), SEND_KEYS_METHOD, password);
        invokeMethod(driver.findElement(By.id(submitBtnId)), CLICK_METHOD);
    }

    /**
     * 退出系统
     * @param logoutId The logout label id.
     * @param confirmId The confirm Dialog button id.
     */
    public void logout(String logoutId, String... confirmId) {
        invokeMethod(driver.findElement(By.id(logoutId)), "click");
        if(confirmId == null || confirmId.length == 0){
            return;
        }
        for(String id: confirmId){
            invokeMethod(driver.findElement(By.id(id)), "click");
        }
    }

    /**
     * 关闭浏览器
     */
    public void closeBrowser(){
        driver.quit();
    }

    /**
     * 点击组件
     * @param elementType The element type of the component.
     * @param key The key word of the element type.
     */
    public void click(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        invokeMethod(element, "click");
    }

    /**
     * 查找元素
     * @param elementType The search type of the component.
     * @param key The key word of the search type.
     * @return
     */
    public WebElement searchElement(String elementType, String key, WebElement... webElements){

        if(StringUtils.isEmpty(elementType)){
            throw new NullPointerException("param elementType is empty!");
        }
        // search区域 默认在WebDriver中搜索
        boolean searchType = true;
        if(webElements != null && webElements.length != 0){
            // search区域在WebElement中查找
            searchType = false;
        }
        List<String> list = Arrays.asList(ID.getElementType(), TAG_NAME.getElementType(),
                NAME.getElementType(), CLASS_NAME.getElementType(), CSS_SELECTOR.getElementType(),
                LINK_TEXT.getElementType(), PARTIAL_LINK_TEXT.getElementType());
        elementType = elementType.toLowerCase();
        if(!list.contains(elementType)){
            throw  new NullPointerException("element type : " + elementType
                    + " can not find!");
        }
        WebElement element = null;
        try {
            if(searchType){
                if(ID.getElementType().equals(elementType)){
                    element = driver.findElement(By.id(key));
                }else if(TAG_NAME.getElementType().equals(elementType)){
                    element = driver.findElement(By.tagName(key));
                }else if(NAME.getElementType().equals(elementType)){
                    element = driver.findElement(By.name(key));
                }else if(CLASS_NAME.getElementType().equals(elementType)){
                    element = driver.findElement(By.className(key));
                }else if(CSS_SELECTOR.getElementType().equals(elementType)){
                    element = driver.findElement(By.cssSelector(key));
                }else if(LINK_TEXT.getElementType().equals(elementType)){
                    element = driver.findElement(By.linkText(key));
                }else if(PARTIAL_LINK_TEXT.getElementType().equals(elementType)){
                    element = driver.findElement(By.partialLinkText(key));
                }else if(XPATH.getElementType().equals(elementType)){
                    element = driver.findElement(By.xpath(key));
                }
            }else{
                WebElement field = webElements[0];
                if(ID.getElementType().equals(elementType)){
                    element = field.findElement(By.id(key));
                }else if(TAG_NAME.getElementType().equals(elementType)){
                    element = field.findElement(By.tagName(key));
                }else if(NAME.getElementType().equals(elementType)){
                    element = field.findElement(By.name(key));
                }else if(CLASS_NAME.getElementType().equals(elementType)){
                    element = field.findElement(By.className(key));
                }else if(CSS_SELECTOR.getElementType().equals(elementType)){
                    element = field.findElement(By.cssSelector(key));
                }else if(PARTIAL_LINK_TEXT.getElementType().equals(elementType)){
                    element = field.findElement(By.partialLinkText(key));
                }else if(XPATH.getElementType().equals(elementType)){
                    element = field.findElement(By.xpath(key));
                }else if(LINK_TEXT.getElementType().equals(elementType)){
                    element = field.findElement(By.linkText(key));
                }
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
        return element;
    }


    /**
     * 点击超链接文本
     * @param key The link text.
     */
    public void clickLink(String key){
        if(StringUtils.isEmpty(key)){
            throw new NullPointerException("param key is null!");
        }
        WebElement element = searchElement(LINK_TEXT.getElementType(), key);
        invokeMethod(element, "click");
    }

    /**
     *  切换 switch
     * @param switchLabel
     */
    public void clickSwitchLabel(WebElement switchLabel){
        if(switchLabel == null){
            throw new NullPointerException("param element is null!");
        }
        switchLabel.click();
    }

    /**
     * 下拉框选择某一项
     * @param elementType The search type.
     * @param key The key word of the search type.
     * @param text The key word of send key.
     */
    public void selectDropDownBox(String elementType, String key, String text){
        if(StringUtils.isEmpty(text)){
            return;
        }
        WebElement dropDownBox = searchElement(elementType, key);
        dropDownBox.sendKeys(text);
    }

    /**
     * 文本框输入
     * @param elementType The search type.
     * @param key The key word of the search type.
     * @param value The key word of send key.
     */
    public void feedTextBox(String elementType, String key, String value){
        WebElement textBox = searchElement(elementType, key);
        textBox.sendKeys(value);
    }

    /**
     * 期望看到组件
     * @param elementType  The element type of the component.
     * @param key The key word of the element type.
     */
   public void expectToSee(String elementType, String key){
       WebElement element = searchElement(elementType, key);
       if(element == null){
           throw new NullPointerException("can't expect to see the element!");
       }
   }

    /**
     * 期望看不到某组件
     * @param elementType The search type.
     * @param key The key word of the search type.
     */
   public void expectNotToSee(String elementType, String key){
       WebElement element = null;
       try{
           element = searchElement(elementType, key);
       }catch(Exception e){
       }
       if(element != null){
           throw new NullPointerException("can expect to see the element!");
       }
   }
    /**期望看到表中某个格内是某个值
     */
    public void expectToSeeFieldInTable(String tableElementType, String key, String defkey, String defValue, String findkey, String elementType, String expectValue) {
	WebElement t = findTable(tableElementType, key);
	WebElement e = findFieldInTable(t, defkey, defValue, findkey);
	expectToSeeValue(e, elementType, expectValue);
    }
    /**
     *  期望看到的链接文本
     * @param key The key word of this search type.
     */
   public void exceptToSeeLinkText(String key){
       WebElement element = searchElement(LINK_TEXT.getElementType(), key);
       if(element == null){
           throw new NullPointerException("can not expect to see the link text element!");
       }
   }

    /**
     * 期望无法看到链接文本
     * @param key
     */
   public void expectNotToSeeLinkText(String key){
       WebElement element = null;
       try{
           element =  searchElement(LINK_TEXT.getElementType(), key);
       }catch(Exception e){
       }
       if(element != null){
           throw new NullPointerException("can expect to see the link text element!");
       }
   }


    /**
     *  区域中search,期望看到某元素
     * @param field The search field.
     * @param elementType The search type.
     * @param key The key word of the search type.
     */
   public void expectToSeeValue(WebElement field, String elementType,String  key){
       if(field == null){
           throw new NullPointerException("The search filed is null!");
       }
       WebElement element = searchElement(elementType, key, field);
       if(element == null){
           throw new NullPointerException("can't expect to see element int the field");
       }
   }

    /**
     *  区域中search,期望看不到某元素
     * @param field The search field.
     * @param elementType The search type.
     * @param key The key word of the search type.
     */
   public void expectNotToSeeValue(WebElement field, String elementType,String  key){
       if(field == null){
           throw new NullPointerException("The search filed is null!");
       }
       WebElement element = searchElement(elementType, key, field);
       if(element != null){
           throw new NullPointerException("can expect to see element int the field");
       }
   }

    /**
     * 查找表格
     * @param elementType The search type.
     * @param key The key word of the search type.
     * @return
     */
   public WebElement findTable(String elementType, String key){

       WebElement element =  searchElement(elementType, key);
       String tagName = element.getTagName();
       if(StringUtils.equalsIgnoreCase(TABLE.getComponentType(), tagName)){
           return element;
       }else{
           throw new NoSuchElementException("can't find table, "
                   + "the type of the found element can't match table!");
       }
   }


    /**
     * 表格中search 单元格
     * @param table
     * @param defkey
     * @param defValue
     * @param findkey
     * @return
     */
   public WebElement findFieldInTable(WebElement table, String defkey
           , String defValue, String findkey){
       if(table == null){
           throw new NullPointerException("The search table  is null!");
       }
       if(StringUtils.isEmpty(defkey) || StringUtils.isEmpty(defValue)){
           return null;
       }
       List<String> metaList = new LinkedList<String>();
       for (WebElement metaElement : table.findElements(By.tagName("th"))) {
           metaList.add(metaElement.getText());
       }
       int defIndexOfMeta = metaList.indexOf(defkey);
       int indexOfMeta = metaList.indexOf(findkey);
       List<WebElement> webElements = table.findElements(By.tagName("tr"));
       if(defIndexOfMeta == -1 || indexOfMeta == -1
               || webElements == null || webElements.size() == 1){
           return null;
       }
       WebElement trElement = null;
       for (int i = 1; i < webElements.size(); i++) {
           String findValue = webElements.get(i).findElements(By.tagName("td"))
                   .get(defIndexOfMeta).getText();
           if(StringUtils.equals(defValue, findValue)){
               trElement =  webElements.get(i);
               break;
           }
       }
       return trElement != null? trElement.findElements(By.tagName("td")).get(indexOfMeta) : null;
   }

    /**
     * 查找文本输入框
     * @param elementType
     * @param key
     * @return
     */
    
    public WebElement findText(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        String componentType = element.getAttribute(TYPE.getComponentType());
        if(StringUtils.equalsIgnoreCase(TEXT.getComponentType()
                , componentType)){
            return element;
        }else{
            throw new NoSuchElementException("can't find text, "
                    + "the type of the found element can't match text!");
        }
    }

    /**
     * 查找下拉菜单
     * @param elementType
     * @param key
     * @return
     */
    public WebElement findSelect(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        String tagName = element.getTagName();
        if(StringUtils.equalsIgnoreCase(SELECT.getComponentType(), tagName)){
            return element;
        }else{
            throw new NoSuchElementException("can't find select, "
                    + "the type of the found element can't match select!");
        }
    }
}



