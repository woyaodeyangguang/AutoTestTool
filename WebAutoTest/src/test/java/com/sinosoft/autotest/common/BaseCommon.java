package com.sinosoft.autotest.common;


import com.sinosoft.autotest.constant.BasicComponentEnum;
import org.apache.commons.lang3.StringUtils;
import org.openqa.selenium.By;
import org.openqa.selenium.Keys;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.ie.InternetExplorerDriver;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.remote.DesiredCapabilities;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.io.File;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Properties;
import java.util.concurrent.TimeUnit;

import static com.sinosoft.autotest.constant.ElementTypeEnum.*;
import static com.sinosoft.autotest.constant.FormComponentTypeEnum.*;
import static com.sinosoft.autotest.constant.BasicComponentEnum.*;
import static java.awt.event.KeyEvent.*;


/**
 * 自动化测试基础函数库
 * @author  unascribed
 * @see     java.lang.Class
 * @since   JDK1.5, Selenium 3.0.0 beta3, Chrome v52-v54 ChromeDriver v2.24
 */
public class BaseCommon {
    private final String SEND_KEYS_METHOD = "sendKeys";
    private final String CLEAR_METHOD ="clear";
    private final String CLICK_METHOD = "click";

    // The configuration properties
    private static Properties configProperties = new Properties();

    private static Keyboard keyboard = null;

    private static List<String> tableHeaderInfo = new ArrayList<String>();

    static {
        try {
            configProperties = PropertyUtils.readProperties();
            keyboard = new Keyboard();
        } catch (AWTException e) {
            System.err.println("-----资源初始化失败-----");
        }
    }


    // The default preposition delay time
    private  long defaultPreDelayTime = Long.valueOf(String.valueOf(
            configProperties.get(DEFAULT_PRE_DELAY_TIME.getBasicComponentInfo())));
    // The default postposition delay time 1600(proper)
    private  long defaultPostDelayTime = Long.valueOf(String.valueOf(
            configProperties.get(DEFAULT_POST_DELAY_TIME.getBasicComponentInfo())));

    // Basic component WebDriver
    private static WebDriver driver;

    public WebDriver getDriver() {
        return driver;
    }

    public void setDriver(WebDriver driver) {
        BaseCommon.driver = driver;
    }

    private static WebDriverWait wait;

    private Actions actions;


    /**
     * 构建基础组件
     * @param browserType The type of browser you want to init.
     */
    public BaseCommon(BasicComponentEnum browserType) {
        initComponent(browserType);
    }

    /**
     * 默认初始化Chrome浏览器组件
     */
    public BaseCommon(){
        this(CHROME);
    }

    /**
     * 初始化基础组件
     * @param browserType The type of browser you want to init.
     */
    public void initComponent(BasicComponentEnum browserType){
        if(CHROME == browserType){
            String webDriverPath = String.valueOf(
                    configProperties.get(WEB_DRIVER_PATH.getBasicComponentInfo()));
            System.setProperty("webdriver.chrome.driver", webDriverPath);
            driver = new ChromeDriver();
        }else  if(FIREFOX == browserType) {
            driver = new FirefoxDriver();
        }else if(IE == browserType) {
            String ieWebDriverPath = String.valueOf(
                    configProperties.get(IE_WEB_DRIVER_PATH.getBasicComponentInfo()));
            System.setProperty("webdriver.ie.driver", ieWebDriverPath);
            //  代码关闭IE一些配置
            DesiredCapabilities ieCapabilities = DesiredCapabilities.internetExplorer();
            ieCapabilities.setCapability(InternetExplorerDriver.INTRODUCE_FLAKINESS_BY_IGNORING_SECURITY_DOMAINS, true);
            driver = new InternetExplorerDriver(ieCapabilities);
        }else {
            throw new RuntimeException("init base component fail, can't match browser type!");
        }
        driver.manage().window().maximize();
        driver.manage().timeouts().implicitlyWait(10, TimeUnit.SECONDS);
        wait = new WebDriverWait(driver, 10);
        // set implict timeout
        driver.manage().timeouts().implicitlyWait(
                Long.valueOf(configProperties.get(IMPLICITLY_WAIT_TIMEOUT.getBasicComponentInfo()).
                        toString()), TimeUnit.SECONDS);
        actions = new Actions(driver);
    }

    /**
     * 初始化基础组件
     */
    public void initComponent(){
        initComponent(CHROME);
    }

    /**
     * 修改执行动作的延迟时间.
     * @param preDelayTime The default preposition delay time
     * @param postDelayTime The default postposition delay time
     */
    public void initDelayTime(long preDelayTime, long postDelayTime) {
        defaultPreDelayTime = preDelayTime;
        defaultPostDelayTime = postDelayTime;
    }

    /**
     * 延迟执行driver中方法
     * @param object The WebElement object.
     * @param methodName The method name of the WebElement object.
     * @param args The arguments.
     */
    public void invokeMethod(Object object, String methodName, String... args) {
        if (StringUtils.isEmpty(methodName) || object == null) {
            throw new RuntimeException("invoke object or method is illegal empty");
        }

        Class[] parameterTypes = new Class[args.length];
        for (int i = 0; i < args.length ; i++) {
            if (args[i].getClass() == String.class && SEND_KEYS_METHOD.equals(methodName)) {
                ((WebElement)object).sendKeys(args);
                return;
            } else {
                parameterTypes[i]= args[i].getClass();
            }
        }
        synchronized (this){
            // The flag to determine to retry
            boolean retry = false;
            int retryTimes = Integer.valueOf(String.valueOf(
                    configProperties.get(INVOKE_METHOD_RETRY_TIMES.getBasicComponentInfo())));
            while(!retry && retryTimes!= 0){
                try {
                    Class clazz = object.getClass();
                    Method method = clazz.getMethod(methodName, parameterTypes);
                    Thread.currentThread().sleep(defaultPreDelayTime);
                    Object result = method.invoke(object, args);
                    Thread.currentThread().sleep(defaultPostDelayTime);
                    retry = true;
                } catch (Exception e) {
                    System.out.println("----------------invokeMethod fail----------------");
                    retryTimes--;
                    e.printStackTrace();
                }
            }
        }
    }

    /**
     * 登录系统
     * @param projectName The projectName, the basic url of this project will open.
     * @param inputUsernameId The username input id.
     * @param username The login username.
     * @param selectRoleId The select role id.
     * @param inputPasswordId The password input id.
     * @param password The login password.
     * @param  submitBtnId The submit button id.
     * @param selectRoleType The selected role type, when the user has many roles.
     */
    public void login(String projectName, String inputUsernameId, String username
            , String selectRoleId, String inputPasswordId, String password
            , String submitBtnId, String... selectRoleType) {

        // when browser is closed, invoke login must init basic component.
        if(driver == null){
            initComponent();
        }
        String url = configProperties.getProperty(projectName);
        if(StringUtils.isEmpty(url)){
            throw new RuntimeException("can't get login url");
        }
        driver.get(url);
        invokeMethod(driver.findElement(By.id(inputUsernameId)), CLEAR_METHOD);
        invokeMethod(driver.findElement(By.id(inputUsernameId)), SEND_KEYS_METHOD, username);
        driver.findElement(By.id(inputUsernameId)).sendKeys(Keys.TAB);

        try{
            Thread.currentThread().sleep(800);
        }catch(Exception e){
        }

        if(selectRoleType != null && selectRoleType.length ==1){
            selectDropDownBoxByText(ID.getElementType(), selectRoleId, selectRoleType[0]);
        }
        invokeMethod(driver.findElement(By.id(inputPasswordId)), CLEAR_METHOD);
        invokeMethod(driver.findElement(By.id(inputPasswordId)), SEND_KEYS_METHOD, password);
        invokeMethod(driver.findElement(By.id(submitBtnId)), CLICK_METHOD);
        if(StringUtils.equals(PALACE.getBasicComponentInfo(), projectName)){
            closeFirstChangePwdDialog();
        }
    }

    /**
     * 退出系统
     * @param logoutId The logout label id.
     * @param confirmId The confirm Dialog button id or ids.
     */
    public void logout(String logoutId, String... confirmId) {
        invokeMethod(driver.findElement(By.id(logoutId)), CLICK_METHOD);
        if(confirmId == null || confirmId.length == 0){
            return;
        }
        for(String id: confirmId){
            invokeMethod(driver.findElement(By.id(id)), CLICK_METHOD);
        }
    }

    /**
     * 关闭浏览器
     */
    public void closeBrowser(){
        if(driver != null) {
          driver.quit();
          driver = null;
        }
    }

    /**
     * 点击组件
     * @param elementType The element type which you want to find a component.
     * @param key The key word of the element type.
     */
    public void click(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        invokeMethod(element, CLICK_METHOD);
    }

    /**
     * 鼠标悬停在 onElement 元素的位置
     * @param element The element which you want to hold.
     */
    public void clickAndHold(WebElement element) {
        actions.clickAndHold(element);
    }

    /**
     * 查找元素
     * @param elementType The element type which you want to find a component.
     * @param key The key word of the element type.
     * @param  webElements The search will occur in this web element.
     * @return The found component of WebElement.
     */
    private WebElement searchElement(String elementType, String key, WebElement... webElements){

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
                LINK_TEXT.getElementType(), PARTIAL_LINK_TEXT.getElementType(),
                XPATH.getElementType());
        elementType = elementType.toLowerCase();
        if(!list.contains(elementType)){
            throw  new NullPointerException("element type : " + elementType
                    + " can not find!");
        }

        // The flag to determine to retry
        boolean retry = false;
        int retryTimes = Integer.valueOf(String.valueOf(
                configProperties.get(SEARCH_ELEMENT_RETRY_TIMES.getBasicComponentInfo())));
        WebElement element = null;
        while(!retry && retryTimes != 0){
            try {
                if(searchType) {
                    if (ID.getElementType().equals(elementType)) {
                        element = driver.findElement(By.id(key));
                    } else if (TAG_NAME.getElementType().equals(elementType)) {
                        element = driver.findElement(By.tagName(key));
                    } else if (NAME.getElementType().equals(elementType)) {
                        element = driver.findElement(By.name(key));
                    } else if (CLASS_NAME.getElementType().equals(elementType)) {
                        element = driver.findElement(By.className(key));
                    } else if (CSS_SELECTOR.getElementType().equals(elementType)) {
                        element = driver.findElement(By.cssSelector(key));
                    } else if (LINK_TEXT.getElementType().equals(elementType)) {
                        element = driver.findElement(By.linkText(key));
                    } else if (PARTIAL_LINK_TEXT.getElementType().equals(elementType)) {
                        element = driver.findElement(By.partialLinkText(key));
                    } else if (XPATH.getElementType().equals(elementType)) {
                        element = driver.findElement(By.xpath(key));
                    }
                }else{
                    WebElement field = webElements[0];
                    if (ID.getElementType().equals(elementType)) {
                        element = field.findElement(By.id(key));
                    } else if (TAG_NAME.getElementType().equals(elementType)) {
                        element = field.findElement(By.tagName(key));
                    } else if (NAME.getElementType().equals(elementType)) {
                        element = field.findElement(By.name(key));
                    } else if (CLASS_NAME.getElementType().equals(elementType)) {
                        element = field.findElement(By.className(key));
                    } else if (CSS_SELECTOR.getElementType().equals(elementType)) {
                        element = field.findElement(By.cssSelector(key));
                    } else if (PARTIAL_LINK_TEXT.getElementType().equals(elementType)) {
                        element = field.findElement(By.partialLinkText(key));
                    } else if (XPATH.getElementType().equals(elementType)) {
                        element = field.findElement(By.xpath(key));
                    } else if (LINK_TEXT.getElementType().equals(elementType)) {
                        element = field.findElement(By.linkText(key));
                    }
                }
                retry = true;
            } catch (Exception e) {
                System.out.println("----------------searchElement fail----------------");
                retryTimes--;
                e.printStackTrace();
            }
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
        invokeMethod(element, CLICK_METHOD);
    }

    /**
     *  点击切换switch控件
     * @param switchLabel The web elemnt of switch label.
     */
    public void clickSwitchLabel(WebElement switchLabel){
        if(switchLabel == null){
            throw new NullPointerException("param element is null!");
        }
        switchLabel.click();
    }

    /**
     * 通过下拉选项value值查找下拉框某一项
     * @param elementType The element type which you want to find a select dropdown box.
     * @param key The key word of element type.
     * @param value The value of select option component.
     */
    public void selectDropDownBox(String elementType, String key, String value){
        WebElement element = searchElement(elementType, key);
        Select select = new Select(element);
        select.selectByValue(value);
    }

    /**
     * 通过下拉选项text值查找下拉框某一项(仅支持原生selecte option)
     * @param elementType The element type which you want to find a select dropdown box.
     * @param key The key word of element type.
     * @param text The value of select option component.
     */
    public void selectDropDownBoxByText(String elementType, String key, String text){
        WebElement element = searchElement(elementType, key);
        Select select = new Select(element);
        select.selectByVisibleText(text);
    }

    /**
     * 通过下拉选项中索引项Index来查找下拉框中某一项(仅支持原生select option)
     * @param elementType The element type which you want to find a select dropdown box.
     * @param key The key word of element type.
     * @param index The index of select option component.
     */
    public void selectDropDownBoxByIndex(String elementType, String key, String index){
        WebElement element = searchElement(elementType, key);
        Select select = new Select(element);
        select.selectByIndex(Integer.parseInt(index));
    }


    /**
     * 文本框输入
     * @param elementType The element type which you want to find a textbox.
     * @param key The key word of element type.
     * @param value The key word of send key .
     */
    public void feedTextBox(String elementType, String key, String value){
        WebElement textBox = searchElement(elementType, key);
        if (StringUtils.equals("", value)){
            invokeMethod(textBox, CLEAR_METHOD);
        }
        if(!StringUtils.isEmpty(value)){
            invokeMethod(textBox, CLEAR_METHOD);
            invokeMethod(textBox, SEND_KEYS_METHOD, value);
        }
    }

    /**
     * 清空 文本框
     * @param elementType The element type which you want to find a textbox.
     * @param key The key word of element type.
     */
    public void clearTextBox(String elementType, String key){
        WebElement textBox = searchElement(elementType, key);
        invokeMethod(textBox, CLEAR_METHOD);
    }

    /**
     * 期望看到组件
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
     */
    public void expectToSee(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        if(element == null){
            throw new NullPointerException("can't expect to see the element!");
        }
    }

    /**
     * 期望看不到某组件
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
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

    /**
     *  期望看到的链接文本
     * @param key The key word of this link.
     */
    public void expectToSeeLinkText(String key){
        WebElement element = searchElement(LINK_TEXT.getElementType(), key);
        if(element == null){
            throw new NullPointerException("can not expect to see the link text element!");
        }
    }

    /**
     * 期望无法看到链接文本
     * @param key The key word of this link.
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
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
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
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
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
     * 期望看到控件 某一属性值
     * @param elementType The element type which you want to find a component.
     * @param key  The key word of element type.
     * @param attr The attribute of the component.
     * @param attrValue The value of the component attribute
     */
    public void expectToSeeAttrValue(String elementType, String key, String attr, String attrValue){
        WebElement element = searchElement(elementType, key);
        String attrs = element.getAttribute(attr);
        if(attrs != null && !attrs.contains(attrValue)){
            throw  new RuntimeException(" attribute of this component " +
                    "can't match expect attribute  value");
        }
    }

    /**
     * 期望看不到控件 某一属性值
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
     * @param attr The attribute of the component.
     * @param attrValue The value of the component attribute
     */
    public void expectNotToSeeAttrValue(String elementType, String key, String attr,
                                        String attrValue){
        WebElement element = searchElement(elementType, key);
        String attrs = element.getAttribute(attr);
        if(attrs != null && attrs.contains(attrValue)){
            throw  new RuntimeException(" attribute of this component " +
                    "can expect to see this attribute ");
        }
    }

    /**
     * 查找表格
     * @param elementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @return
     */
    private WebElement findTable(String elementType, String key){
        WebElement element =  searchElement(elementType, key);
        return element;

    }

    /**
     * 表格（属性按行组织）中search 单元格
     * @param table The web element of table component.
     * @param defKey The attribute of table header to define a row.
     * @param defValue The value  of this attribute to define a row.
     * @param findKey The attribute of table header to find.
     * @param args The args in which you can put another attribute and it's value to define a row.
     * @return Field web element.
     */
    private WebElement findFieldInTable(WebElement table, String defKey
            , String defValue, String findKey, String... args){
        if(table == null){
            throw new NullPointerException("The search table  is null!");
        }
        if(StringUtils.isEmpty(defKey) || StringUtils.isEmpty(defValue)){
            return null;
        }
        if(args != null && args.length != 2 && args.length != 0){
            throw new RuntimeException("find field in table, illegal arguments");
        }
        List<String> metaList = getTableHeaderInfo(table);
        int defIndexOfMeta = metaList.indexOf(defKey);
        int indexOfMeta = metaList.indexOf(findKey);
        List<WebElement> webElements = table.findElements(By.tagName(TR.getComponentType()));
        // if web elements' size is only 1, it only may contains a row of attribute header.
        if(defIndexOfMeta == -1 || indexOfMeta == -1 || webElements == null){
            return null;
        }
        WebElement trElement = null;
        for (int i = 0; i < webElements.size(); i++) {
            List<WebElement> tdElements = webElements.get(i).findElements(
                    By.tagName(TD.getComponentType()));
            // ignore  row which doesn't contains td element.
            if(tdElements == null || tdElements.size() == 0){
                continue;
            }
            String findValue = tdElements.get(defIndexOfMeta).getText();
            if(StringUtils.equals(defValue, findValue)){
                // consider a defKey an defValue can't define a row.
                if(args != null && args.length == 2){
                    String defKeyNew = args[0];
                    String defValueNew = args[1];
                    String findValueNew = tdElements.get(metaList.indexOf(defKeyNew)).getText();
                    if(StringUtils.equals(defValueNew, findValueNew)){
                        trElement =  webElements.get(i);
                        break;
                    }
                }else{
                    trElement =  webElements.get(i);
                    break;
                }
            }
        }
        return trElement != null? trElement.findElements(By.tagName(TD.getComponentType()))
                .get(indexOfMeta) : null;
    }


    /**
     * 获取表头信息
     * @param table The table.
     * @return The meta info with list.
     */
    private List<String> getTableHeaderInfo(WebElement table){
        List<String> metaList = new LinkedList<String>();
        // 优先找th标签元素
        for (WebElement metaElement : table.findElements(By.tagName(TH.getComponentType()))) {
            if(!metaList.contains(metaElement.getText()) && !StringUtils.isEmpty(metaElement.getText())){
                metaList.add(metaElement.getText());
            }
        }
        // 如果找不到，返回经过显示初始化
        if(metaList == null || metaList.size() == 0){
           return tableHeaderInfo;
        }
        tableHeaderInfo = metaList;
        return metaList;
    }

    /**
     * 初始化表头属性，当表格不符合规则时，可以直接初始化表头数据
     * @param tableHeaders The table header attribute.
     */
    public void initTableHeaderInfo(String... tableHeaders) {
        if(tableHeaders == null || tableHeaders.length == 0) {
            return;
        }
        for (String tableHeader : tableHeaders){
            if(!StringUtils.isEmpty(tableHeader)) {
                tableHeaderInfo.add(tableHeader);
            }
        }
    }

    /**
     * 初始化表头属性,当表格不符合规范（即不包含th元素）时，需要调用该函数
     * @param elementType The element type which you want to find a table
     * @param key The key word of element type.
     */
    public void initTableHeaderInfo(String elementType, String key){
        tableHeaderInfo = new ArrayList<String>();
        WebElement tableHeader = searchElement(elementType, key);
        // 优先找th标签元素
        for (WebElement metaElement : tableHeader.findElements(By.tagName(TH.getComponentType()))) {
            if(!tableHeaderInfo.contains(metaElement.getText())){
                tableHeaderInfo.add(metaElement.getText());
            }
        }
        // 如果找不到，再找td标签标签元素
        if(tableHeaderInfo == null || tableHeaderInfo.size() == 0){
            for (WebElement metaElement : tableHeader.findElements(By.tagName(TR.getComponentType()))
                    .get(0).findElements(By.tagName(TD.getComponentType()))) {
                if(!tableHeaderInfo.contains(metaElement.getText())){
                    tableHeaderInfo.add(metaElement.getText());
                }
            }
        }
    }




    /**
     * 表格（属性按列组织）中search 单元格
     * @param table The web element of table component table.
     * @param findKey The attribute of table header to find.
     * @param pos The distance of table attribute.
     * @return Field web element.
     */
    private WebElement findFieldInTable(WebElement table, String findKey, int... pos){
        if(table == null){
            throw new RuntimeException("web elment table is empty");
        }
        // move distance
        int distance = 1;
        if(pos != null && pos.length == 1 && pos[0] > 0){
            distance = pos[0];
        }
        List<WebElement> trElements = table.findElements(By.tagName(TR.getComponentType()));
        WebElement findElement = null;
        boolean flag = false;
        for(int i = 0; i < trElements.size() && !flag; i++){
            List<WebElement> tdElements = trElements.get(i)
                    .findElements(By.tagName(TD.getComponentType()));
            for (int j = 0; j < tdElements.size(); j++) {
                if(StringUtils.equals(tdElements.get(j).getText(), findKey)){
                    findElement = tdElements.get(j + distance);
                    flag = true;
                    break;
                }
            }
        }
        return findElement;
    }


    /**
     * 期望看不到表格（属性按行组织）中某一行
     * @param elementType The element type which you want to find a table
     * @param key The key word of element type.
     * @param defKey The attribute of table header to define a row.
     * @param defValue The value  of this attribute to define a row.
     */
    public void expectNotToSeeRowInTable(String elementType, String key, String defKey
            , String defValue){
        WebElement table = findTable(elementType, key);
        if(StringUtils.isEmpty(defKey) || StringUtils.isEmpty(defValue)){
            throw new RuntimeException(" No such key ");
        }
        List<String> metaList = getTableHeaderInfo(table);
        int defIndexOfMeta = metaList.indexOf(defKey);
        List<WebElement> webElements = table.findElements(By.tagName(TR.getComponentType()));
        // if web elements' size is only 1, it only contains a row of attribute header.
        if(defIndexOfMeta == -1 || webElements == null || webElements.size() == 1){
             throw new RuntimeException(" No such attribute");
        }
        for (int i = 0; i < webElements.size(); i++) {
            String findValue = null;
            try{
                findValue = webElements.get(i).findElements(By.tagName(TD.getComponentType()))
                        .get(defIndexOfMeta).getText();
            }catch (Exception e){
                findValue = null;
            }
            if(findValue != null && StringUtils.equals(defValue, findValue)){
                 throw  new RuntimeException(" attribute of this component " +
                        "can expect to see this attribute ");
            }
        }
    }


    /**
     * 点击表格（属性按列组织）中偏移具体为pos的单元格
     * @param tableElementType The element type which you want to find a table
     * @param tableKey The key word of this table element type.
     * @param defkey The key word of attribute header.
     * @param pos The position distance of this attribute header.
     * @param elementType The element type which you want to find a component in field.
     * @param key The key word of this component in this field.
     */
    public void clickRandomFieldInTable(String tableElementType, String tableKey, String defkey
            , int pos, String elementType, String key) {
        WebElement table = findTable(tableElementType, tableKey);
        WebElement fieldInTable = findFieldInTable(table, defkey, pos);
        if(fieldInTable == null){
            throw new RuntimeException("can't find this field, can't click");
        }
		WebElement ff = searchElement(elementType, key, fieldInTable);
        if(!ff.findElement(By.xpath("..")).isDisplayed()){
            sleep(1);
            actions.moveToElement(fieldInTable).build().perform();
            sleep(1);
        }
        invokeMethod(ff, CLICK_METHOD);

    }
    /**
     * 查找表格（属性按行组织）中某一个单元格文本值
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param defkey The attribute of table header to define a row.
     * @param defValue The value  of this attribute to define a row.
     * @param findkey The attribute of table header to find.
     * @return The text of found field web element.
     */
    public String getFieldTextInTable(String tableElementType, String key, String defkey
            , String defValue, String findkey) {
        WebElement table = findTable(tableElementType, key);
        WebElement fieldInTable = findFieldInTable(table, defkey, defValue, findkey);
        return fieldInTable != null ? fieldInTable.getText() : null;
    }

    /**
     * 查找表格（属性按列组织）中某一个单元格文本值
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param defkey The attribute of table header to define a row.
     * @return The text of found field web element.
     */
    public String getFieldTextInTable(String tableElementType, String key, String defkey){
        WebElement table = findTable(tableElementType, key);
        WebElement fieldInTable = findFieldInTable(table, defkey);
        return fieldInTable != null ? fieldInTable.getText() : null;
    }



    /**
     * 表格中查找某一行
     * @param table The element type which you want to find a table.
     * @param defKey The attribute of table header to define a row.
     * @param defValue The value  of this attribute to define a row.
     * @return A found row in this table.
     */
    private WebElement searchTableItem(WebElement table, String defKey, String defValue){
        if(table == null){
            throw new NullPointerException("The search table  is null!");
        }
        // return table th row （Table header）
        if(StringUtils.equalsIgnoreCase(defKey, defValue)){
            return table.findElements(By.tagName(TH.getComponentType())).get(0);
        }
        List<String> metaList = getTableHeaderInfo(table);
        int defIndexOfMeta = metaList.indexOf(defKey);
        List<WebElement> webElements = table.findElements(By.tagName(TR.getComponentType()));
        WebElement trElement = null;
        for (int i = 0; i < webElements.size(); i++) {
            String findValue = null;
            try{
                List<WebElement> tdWebElementsInRow =
                        webElements.get(i).findElements(By.tagName(TD.getComponentType()));
                findValue = tdWebElementsInRow.size() > 0 ?
                        tdWebElementsInRow.get(defIndexOfMeta).getText() : null;
            } catch(Exception e){
                e.printStackTrace();
            }
            if(StringUtils.equals(defValue, findValue)){
                trElement =  webElements.get(i);
                break;
            }
        }
        return trElement;
    }

    /**
     * 期望看到表格（属性按行组织）中某一单元格 文本值
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param defkey The attribute name of table title which you want to define a table row.
     * @param defValue The value of attribute name.
     * @param findkey The attribute name of field which you want to find.
     * @param expectText The text you want to see in this field.
     */
    public void expectToSeeTextInTable(String tableElementType, String key, String defkey
            , String defValue, String findkey, String expectText) {
        WebElement table = findTable(tableElementType, key);
        WebElement fieldInTable = findFieldInTable(table, defkey, defValue, findkey, null);
        if(!StringUtils.equals(fieldInTable.getText(), expectText)){
            throw new RuntimeException("can't expect to see the text in this table");
        }
    }

    /**
     * 期望看到表格(属性按列组织)中某一单元格 文本值
     * @param elementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param defKey The name of the attribute.
     * @param value The expect to see text of this attribute.
     */
    public void expectToSeeTextInTable(String elementType, String key, String defKey, String value){
        WebElement table = findTable(elementType, key);
        List<WebElement> trElements = table.findElements(By.tagName(TR.getComponentType()));
        WebElement findElement = findFieldInTable(table, defKey);
        if (findElement == null) {
            throw new RuntimeException("can't find this field");
        }else{
            if(!StringUtils.equals(findElement.getText(), value)){
                throw new RuntimeException("can't expect to see text in table");
            }
        }
    }

    /**
     * 期望看不到表格（属性按行组织）中某一单元格 文本值
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param defkey The attribute name of table title which you want to define a table row.
     * @param defValue The value of attribute name.
     * @param findkey The attribute name of field which you want to click.
     * @param expectNotText The text you want not to see in this field.
     */
    public void expectNotToSeeTextInTable(String tableElementType, String key, String defkey
            , String defValue, String findkey, String expectNotText) {
        WebElement table = findTable(tableElementType, key);
        WebElement fieldInTable = findFieldInTable(table, defkey, defValue, findkey);
        if(fieldInTable != null && StringUtils.equals(fieldInTable.getText(), expectNotText)){
            throw new RuntimeException("can expect to see the text in this table");
        }
    }


    /**
     * 期望看不到表格(属性按列组织)中某一单元格 文本值
     * @param elementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param defKey The name of the attribute.
     * @param value The expect to see text of this attribute.
     */
    public void expectNotToSeeTextInTable(String elementType, String key, String defKey, String value){
        WebElement table = findTable(elementType, key);
        WebElement findElement = findFieldInTable(table, defKey);
        if (findElement == null) {
            throw new RuntimeException("can't find this field");
        }else{
            if(StringUtils.equals(findElement.getText(), value)){
                throw new RuntimeException("can expect to see text in table");
            }
        }
    }

    /**
     * 期望看到表格（属性按行组织）中所有数据中某一个表头属性为某一文本值
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param  attr The attribute of table header.
     * @param expectValue The value of table header attribute you want expect to see.
     */
    public void expectToSeeAttrValueInTable(String tableElementType, String key, String attr
            , String expectValue){
        int defIndexOfMeta =  getMetaIndexInTable(tableElementType, key, attr);
        List<WebElement> trElements = getTrElementsInTable(tableElementType, key);
        if(defIndexOfMeta == -1){
            throw new RuntimeException("can't find this attribute int this table");
        }
        for (int i = 0; i < trElements.size(); i++) {
            String findValue = null;
            try{
                findValue = trElements.get(i).findElements(By.tagName(TD.getComponentType()))
                        .get(defIndexOfMeta).getText();
            }catch (Exception e){
                findValue = null;
            }
            if(findValue != null && !StringUtils.equals(expectValue, findValue)){
                throw new RuntimeException("can't expect to see attribute value in table");
            }
        }
    }

    /**
     * 期望看到表格（属性按行组织）中所有数据中某一个表头属性包含某一文本值
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param  attr The attribute of table header.
     * @param expectValue The partial value of table header attribute you want expect to see.
     */
    public void expectToSeePartialAttrValueInTable(String tableElementType, String key, String attr
            , String expectValue){
        int defIndexOfMeta =  getMetaIndexInTable(tableElementType, key, attr);
        List<WebElement> trElements = getTrElementsInTable(tableElementType, key);
        if(defIndexOfMeta == -1){
            throw new RuntimeException("can't find this attribute int this table");
        }
        for (int i = 0; i < trElements.size(); i++) {
            String findValue = null;
            try{
                findValue = trElements.get(i).findElements(By.tagName(TD.getComponentType()))
                        .get(defIndexOfMeta).getText();
            }catch (Exception e){
                findValue = null;
            }
            // 如果查找的数据值为null，或者包含表头属性时，不做任何后续逻辑判断
            if(findValue == null || tableHeaderInfo.contains(findValue)){
            	continue;
            }
            if(!StringUtils.isEmpty(findValue) && !StringUtils.contains(findValue, expectValue) &&
                    !StringUtils.equals("没有找到匹配的记录", findValue)){
                throw new RuntimeException("can't expect to see attribute partial value in table");
            }
        }
    }


    /**
     * 期望看到表格（属性按行组织）中属性为某一文本值的偏移Index
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param attr The attribute of table header.
     * @return
     */
    private int getMetaIndexInTable(String tableElementType, String key, String attr){
        WebElement table = findTable(tableElementType, key);
        List<String> metaList = getTableHeaderInfo(table);
        return  metaList.indexOf(attr);
    }

    /**
     * 获取表格（属性按行组织）中所有的行级元素
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @return
     */
    private List<WebElement> getTrElementsInTable(String tableElementType, String key){
        WebElement table = findTable(tableElementType, key);
        return table.findElements(By.tagName(TR.getComponentType()));
    }

    /**
     * 期望看到控件的文本值
     * @param elementType  The element type which you want to find a component.
     * @param key  The key word of element type.
     * @param text Expect to see the text of this component.
     */
    public void expectToSeeText(String elementType, String key, String text){
        WebElement element = searchElement(elementType, key);
        if(!StringUtils.equals(element.getText(), text)){
            throw new RuntimeException("the expect text can't match the text of this component");
        }
    }

    /**
     * 期望看到控件的模糊匹配文本值
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
     * @param partialText The partial text which you want to match.
     */
    public void expectToSeePartialText(String elementType, String key, String partialText){
        WebElement element = searchElement(elementType, key);
        if(!StringUtils.contains(element.getText(), partialText)){
            throw new RuntimeException("the text of this component " +
                    "doesn't contain this partial text");
        }
    }

    /**
     * 期望看到文本框中的 value值
     * @param elementType The element type which you want to find a textbox.
     * @param key The key word of element type.
     * @param value Expect to see the value of this textbox.
     */
    public void expectToSeeValueInTextBox(String elementType, String key, String value){
        WebElement textBox = findTextBox(elementType, key);
        if(!StringUtils.equals(textBox.getAttribute(VALUE.getComponentType()), value)){
            throw new RuntimeException("the expect text can't match the text of this component");
        }
    }

    /**
     * 期望看到下拉菜单选项中存在指定的value值
     * @param elementType The element type which you want to find a drop down box.
     * @param key The key word of element type.
     * @param value The value which you want to see in option of this drop down box.
     */
    public void expectToSeeValueInDropDownBox(String elementType, String key, String value){
        WebElement dropDownBox = findDropDownBox(elementType, key);
        WebElement option = null;
        for(WebElement element : dropDownBox.findElements(By.tagName(OPTION.getComponentType()))){
            if(StringUtils.equals(value, element.getAttribute(VALUE.getComponentType()))){
                option = element;
            }
        }
        if(option == null){
            throw new RuntimeException("can't expect to see value in drop down box option.");
        }
    }

    /**
     * 点击表格（属性列按行）中某一单元格元素
     * @param tableElementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param defkey The attribute name of table title which you want to define a table row.
     * @param defValue The value of attribute name.
     * @param findkey The attribute name of field which you want to click.
     * @param args The args in which you can put another attribute and it's value.
     */
    public void clickFieldInTable(String tableElementType, String key, String defkey
            , String defValue, String findkey, String... args) {
        WebElement table = findTable(tableElementType, key);
        WebElement fieldInTable = findFieldInTable(table, defkey, defValue, findkey, args);
        if(fieldInTable == null){
            throw new RuntimeException("can't find this field, can't click");
        }
        fieldInTable.click();
    }

    /**
     * 点击表格中某一行checkbox（默认checkbox在第一列）
     * @param elementType The element type which you want to find a table.
     * @param key The key word of element type.
     * @param defkey The attribute name of table title which you want to define a table row.
     * @param defValue  The value of attribute name.
     */
    public void clickTableCheckBox(String elementType, String key, String defkey, String defValue) {
        WebElement t = findTable(elementType, key);
        clickTableItemCheckBox(t, defkey, defValue);
    }

     /**
     * 点击表格中某一行checkbox（默认checkbox在第一列）
     * @param table The web element of table.
     * @param defkey The attribute name of table title which you want to define a table row.
     * @param defValue The value of attribute name.
     */
    public void clickTableItemCheckBox(WebElement table, String defkey, String defValue){
        WebElement trElement = searchTableItem(table, defkey, defValue);
        if(trElement == null){
            throw new RuntimeException("cant not find table item in this table, can't click!");
        }
        List<WebElement> checkBoxList = trElement.findElements(
                By.tagName(INPUT.getComponentType()));
        if(checkBoxList == null || checkBoxList.size() != 1){
            throw new RuntimeException("cant not find checkbox in this table," +
                    "or find too many checkbox");
        }
        checkBoxList.get(0).click();
    }

    /**
     * 下拉菜单不希望看到某一选项
     * @param elementType The element type which you want to find a dropdown box.
     * @param key The key word of element type.
     * @param value The option value of dropdown box option.
     */
    public void dropDownBoxNotToSeeValue(String elementType, String key, String value){
        WebElement element = searchElement(elementType, key);
        //element.sendKeys(Keys.TAB);
        if(!StringUtils.equalsIgnoreCase(SELECT.getComponentType(),
                element.getTagName())){
            throw new RuntimeException("the web element tag name can't match select");
        }
        for(WebElement option : element.findElements(
                By.tagName(OPTION.getComponentType()))){
            if(StringUtils.equalsIgnoreCase(value, option.getAttribute(VALUE.getComponentType()))){
                throw new RuntimeException("select dropdown box component can see text");
            }
        }
    }

    /**
     * 下拉菜单中希望看到某一选项
     * @param elementType The element type which you want to find a dropdown box.
     * @param key The key word of element type.
     * @param value The option value of dropdown box
     */
    public void dropDownBoxToSeeValue(String elementType, String key, String value){
        WebElement element = searchElement(elementType, key);
        //element.sendKeys(Keys.TAB);
        if(!StringUtils.equalsIgnoreCase(SELECT.getComponentType(),
                element.getTagName())){
            throw new RuntimeException("the web element tag name can't match select");
        }
        WebElement toSeeOption = null;
        for(WebElement option : element.findElements(
                By.tagName(OPTION.getComponentType()))){
            if(StringUtils.equalsIgnoreCase(value, option.getAttribute(VALUE.getComponentType()))){
                toSeeOption = option;
            }
        }
        if(toSeeOption == null){
            throw new RuntimeException("select dropdown box component can't see text");
        }
    }
	
	    /**
     * 下拉菜单不希望看到某一选项
     * @param elementType The element type which you want to find a dropdown box.
     * @param key The key word of element type.
     * @param value The option value of dropdown box option.
     */
    public void dropDownBoxNotToSeeText(String elementType, String key, String value){
        WebElement element = searchElement(elementType, key);
        //element.sendKeys(Keys.TAB);
        if(!StringUtils.equalsIgnoreCase(SELECT.getComponentType(),
                element.getTagName())){
            throw new RuntimeException("the web element tag name can't match select");
        }
        for(WebElement option : element.findElements(
                By.tagName(OPTION.getComponentType()))){
            if(StringUtils.equalsIgnoreCase(value, option.getText())){
                throw new RuntimeException("select dropdown box component can see text");
            }
        }
    }

    /**
     * 下拉菜单中希望看到某一选项
     * @param elementType The element type which you want to find a dropdown box.
     * @param key The key word of element type.
     * @param value The option value of dropdown box
     */
    public void dropDownBoxToSeeText(String elementType, String key, String value){
        WebElement element = searchElement(elementType, key);
        //element.sendKeys(Keys.TAB);
        if(!StringUtils.equalsIgnoreCase(SELECT.getComponentType(),
                element.getTagName())){
            throw new RuntimeException("the web element tag name can't match select");
        }
        WebElement toSeeOption = null;
        for(WebElement option : element.findElements(
                By.tagName(OPTION.getComponentType()))){
            if(StringUtils.equalsIgnoreCase(value, option.getText())){
                toSeeOption = option;
            }
        }
        if(toSeeOption == null){
            throw new RuntimeException("select dropdown box component can't see text");
        }
    }

    /**
     * 期望看到当前下拉菜单中选择的值
     * @param elementType The element type which you want to find a dropdown box.
     * @param key The key word of element type.
     * @param expectedText The expected text you want to see in this selected option.
     */
    public void dropDownBoxToSeeSelectedText(String elementType, String key, String expectedText){
        WebElement element = searchElement(elementType, key);
        Select select = new Select(element);
        String text = select.getFirstSelectedOption().getText();
        if(!StringUtils.equals(expectedText, text)){
            throw new RuntimeException("can not to see " + expectedText + " in this dropdown box");
        }
    }

    /**
     * 期望表格中无法看到某一项
     * @param table The element type which you want to find a table.
     * @param defKey The attribute name of table title which you want to define a table row.
     * @param defValue The value of attribute name.
     */
    public void tableNotToSeeItem(WebElement table, String defKey, String defValue){
        WebElement tableItem = searchTableItem(table, defKey, defValue);
        if(table != null){
            throw new RuntimeException("can see the item in this table");
        }
    }

    /**
     * 表格中期望看到某一行 The element type which you want to find a table.
     * @param table The element type which you want to find a table.
     * @param defKey The attribute name of table title which you want to define a table row.
     * @param defValue The value of attribute name.
     */
    public void tableToSeeItem(WebElement table, String defKey, String defValue){
        WebElement tableItem = searchTableItem(table, defKey, defValue);
        if(table == null){
            throw new RuntimeException("can't see the item in this table");
        }
    }

    /**
     * 查找文本输入框
     * @param elementType The element type which you want to find a text.
     * @param key The key word of element type.
     * @return The web element of text.
     */
    private WebElement findTextBox(String elementType, String key){
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
     * @param elementType The element type which you want to find a select.
     * @param key The key word of element type.
     * @return The web element of select.
     */
    private WebElement findDropDownBox(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        String tagName = element.getTagName();
        if(StringUtils.equalsIgnoreCase(SELECT.getComponentType(), tagName)){
            return element;
        }else{
            throw new NoSuchElementException("can't find select, "
                    + "the type of the found element can't match select!");
        }
    }

    /**
     * 希望组件是可用（Enable）
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
     */
    public void expectEnable(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        boolean isEnable = element.isEnabled();
        if(!isEnable){
            throw new RuntimeException("the web element is not enable, expect it to be enable");
        }
    }

    /**
     * 希望组件不可用(Disable)
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
     */
    public void expectDisable(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        boolean isEnable = element.isEnabled();
        if(isEnable){
            throw new RuntimeException("the web element is enable, expect it to be disable");
        }
    }

    /**
     * 发送TAB键
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
     */
    public void sendTab(String elementType, String key){
        WebElement element = searchElement(elementType, key);
        element.sendKeys(Keys.TAB);
    }

    /**
     * 发送Enter键
     * sometimes can't work.
     */
    @Deprecated
    private void sendEnterKey(){
        Actions actions = new Actions(driver);
        actions.sendKeys(Keys.ENTER);
    }

    /**
     * 线程睡眠，单位为秒
     * @param sleepSeconds The thread sleep seconds.
     */
    public void sleep(int sleepSeconds){
        try{
            Thread.currentThread().sleep(TimeUnit.SECONDS.toMillis(sleepSeconds));
        } catch(Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 点击应用树中，任一角色checkbox
     * @param system The system which you want to select.
     * @param role The role name in this system.
     * @param id The id of the area you want to search a tree.
     */
    public void clickCheckBoxInTree(String system, String role, String... id){
        WebElement checkbox = searchCheckBoxInTree(system, role, id);
        checkbox.click();
    }


    /**
     * 期望应用树中，任一角色checkbox处于点击状态
     * @param system The system which you want to select.
     * @param role The role name in this system.
     * @param id The id of the area you want to search a tree.
     */
    public void expectToSeeCheckBoxCheckedInTree(String system, String role, String... id){
        WebElement checkbox = searchCheckBoxInTree(system, role, id);
        String attrClass = checkbox.getAttribute(CLASS.getComponentType());
        if(!StringUtils.contains(attrClass, CHECKBOX_TRUE_FULL.getComponentType())){
            throw new RuntimeException("can't expect to see checkbox checked in this tree");
        }
    }

    /**
     * 期望应用树中，任一角色checkbox处于取消点击状态
     * @param system The system which you want to select.
     * @param role The role name in this system.
     * @param id The id of the area you want to search a tree.
     */
    public void expectNotToSeeCheckBoxCheckedInTree(String system, String role, String... id){
        WebElement checkbox = searchCheckBoxInTree(system, role, id);
        String attrClass = checkbox.getAttribute(CLASS.getComponentType());
        if(StringUtils.contains(attrClass, CHECKBOX_TRUE_FULL.getComponentType())){
            throw new RuntimeException("can see checkbox checked in this tree");
        }
    }

    /**
     * 搜索应用树中，任一角色checkbox
     * @param system The system which you want to select.
     * @param role The role name in this system.
     * @param id The id of the area you want to search a tree.
     */
    private WebElement searchCheckBoxInTree(String system, String role, String... id){
        String cssSelector = "a[title='"+ system + "']~ul [title= '"+ role +"']";
        if(id != null && id.length != 0){
            cssSelector = "#" + id[0] + " " + cssSelector;
        }
        String xpath = "preceding-sibling::span[1]";
        WebElement checkbox = searchElement(XPATH.getElementType(), xpath
                , searchElement(CSS_SELECTOR.getElementType(), cssSelector));
        if(checkbox == null){
            throw new RuntimeException("can't find checkbox in tree");
        }
        return checkbox;
    }

    /**
     * 同意当前的对话框(目前支持原生alert、confirm、prompt)
     */
    public void acceptAlert(){
        sleep(1);
        driver.switchTo().alert().accept();
    }

    /**
     * 关闭当前的对话框(目前支持原生alert、confirm、prompt)
     */
    public void dismissAlert(){
        sleep(1);
        driver.switchTo().alert().dismiss();
    }

    /**
     * 切换到浏览器iframe中
     * @param frameId The id of iframe.
     */
    public void switchToFrame(String frameId){
        driver.switchTo().frame(frameId);
    }

    /**
     * 切换到主窗口
     */
    public void switchToDefaultContent(){
        driver.switchTo().defaultContent();
    }

    /**
     * 关闭首次更改密码
     */
     public void closeFirstChangePwdDialog(){
         try{
             if(driver.findElement(By.id("firstChangePwdModal")).isDisplayed()){
                 invokeMethod(driver.findElement(
                         By.cssSelector("#firstChangePwdModal button[data-dismiss='modal']")),
                         CLICK_METHOD);
             }
         }catch(Exception e){
         }
    }

    /**
     * 上传文件（支持原生 input type = "file" 上传, 同时兼容windows上传框)）
     * @param elementType The element type which you want to find a component.
     * @param key The key word of element type.
     * @param filePath The file absolute path.
     * @param useKeyboard The parameter to determine which type want to upload file.
     */
    public void uploadFile(String elementType, String key, String filePath, Object useKeyboard){
        // input type = file 形式文件上传
        if(StringUtils.equalsIgnoreCase((String) useKeyboard, FALSE.getBasicComponentInfo())){
            File uploadFile = new File(filePath);
            if(!uploadFile.exists()){
                throw new RuntimeException("文件" + filePath + ", 无法找到");
            }
            WebElement element = searchElement(elementType, key);
            if(element == null){
                throw new RuntimeException("无法查找到上传组件");
            }
            element.sendKeys(uploadFile.getAbsolutePath());
            // 调用windows上传
        }else if(StringUtils.equalsIgnoreCase((String) useKeyboard, TRUE.getBasicComponentInfo())){
            try {
                WebElement element = searchElement(elementType, key);
                element.click();
                keyboard.getRobot().keyPress(VK_BACK_SPACE);
                Thread.currentThread().sleep(1000);
                keyboard.type(filePath);
                Thread.currentThread().sleep(1500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            keyboard.getRobot().keyPress(KeyEvent.VK_ENTER);
        } else {
            throw new RuntimeException("invalid parameter.");
        }

    }

}
