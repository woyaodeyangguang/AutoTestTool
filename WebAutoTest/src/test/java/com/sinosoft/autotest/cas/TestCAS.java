package com.sinosoft.autotest.cas;

import com.sinosoft.autotest.common.BaseCommon;
import com.sinosoft.autotest.common.PropertyUtils;
import org.junit.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.Keys;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.ui.Select;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

/**
 * 测试CAS登陆
 * 测试时请将鼠标悬停到浏览器最上方，以免影响测试效果
 * Created by Admin on 2017/5/5.
 */
public class TestCAS {
    // The configuration properties
    private static Properties configProperties = PropertyUtils.readProperties();
    private static String projectName = "palace";
    private static String mysqlUrl = "com.mysql.jdbc.Driver";
    // palace test environment
    //private static String dbUrl = "jdbc:mysql://172.20.101.137:3306/gguser";
    // company test environment
    private static String dbUrl = "jdbc:mysql://192.168.100.182:3306/gguser";
    private static String userName = "root";
    private static String passWord = "root";
    private static Connection connection;
    private static  List<String> userNames = new ArrayList<String>();
    private final String SEND_KEYS_METHOD = "sendKeys";
    private final String CLEAR_METHOD ="clear";
    private final String CLICK_METHOD = "click";

    static{
        init();
    }

    @Test
    public void test() throws SQLException {
        BaseCommon baseCommon = new BaseCommon();
        WebDriver driver = baseCommon.getDriver();
        String url = configProperties.getProperty(projectName);
        driver.get(url);
        for (int i = 0; i < userNames.size(); i++)
        {
            String userName = userNames.get(i);
            try{
                // 如果过程中发生异常，则关掉浏览器重新启动
                if(baseCommon.getDriver() == null)
                {
                    baseCommon = new BaseCommon();
                    driver = baseCommon.getDriver();
                    driver.get(url);
                }
                baseCommon.invokeMethod(driver.findElement(By.id("username")), CLEAR_METHOD);
                baseCommon.invokeMethod(driver.findElement(By.id("username")), SEND_KEYS_METHOD, userName);
                driver.findElement(By.id("username")).sendKeys(Keys.TAB);
                Thread.currentThread().sleep(300);
                WebElement selectOrg = driver.findElement(By.id("selectid"));
                if(selectOrg != null && selectOrg.isDisplayed())
                {
                    Select select = new Select(selectOrg);
                    select.selectByIndex(1);
                    System.out.println(userName + "存在多个角色信息");
                }
                baseCommon.invokeMethod(driver.findElement(By.id("password")), CLEAR_METHOD);
                baseCommon.invokeMethod(driver.findElement(By.id("password")), SEND_KEYS_METHOD, "8888");
                baseCommon.invokeMethod(driver.findElement(By.id("submitid")), CLICK_METHOD);
                baseCommon.closeFirstChangePwdDialog();
                //点击头像
                baseCommon.invokeMethod(driver.findElement(By.id("yhicon")), CLICK_METHOD);
                Thread.currentThread().sleep(300);
                baseCommon.invokeMethod(driver.findElement(By.linkText("退出")), CLICK_METHOD);
                Thread.currentThread().sleep(300);
            }catch (Exception e){
                System.err.println(userName + "登陆失败");
                baseCommon.closeBrowser();
            }
        }
        baseCommon.closeBrowser();
    }

    /**
     * 查询数据库获取用户列表
     */
    public static void init() {
        try {
            Class.forName(mysqlUrl);
            connection = DriverManager.getConnection(dbUrl, userName, passWord);
            Statement stmt = connection.createStatement();
            ResultSet rs = stmt.executeQuery("select distinct " +
                    "username from gw_ams_user where status in(1,2)");
            while(rs.next()) {
                String userName = rs.getString("username");
                userNames.add(userName);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }finally {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

}
