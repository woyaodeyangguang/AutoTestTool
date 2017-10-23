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
import static com.sinosoft.autotest.constant.BasicComponentEnum.*;


/**
 * 测试旧CAS登陆
 * 测试时请将鼠标悬停到浏览器最上方，以免影响测试效果
 * Created by Admin on 2017/5/5.
 */
public class TestOldCAS {
    // The configuration properties
    private static Properties configProperties = PropertyUtils.readProperties();
    private static String projectName = "oldPalace";
    private static String logoutUrl = "http://cas.dpm.org.cn/cas/logout";
    private static String mysqlUrl = "com.mysql.jdbc.Driver";
    private static String dbUrl = "jdbc:mysql://172.20.100.111:3306/gguser";
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
        String url = configProperties.getProperty(projectName);
        for (int i = 0; i < userNames.size(); i++) {
        	BaseCommon baseCommon = new BaseCommon(IE);
        	WebDriver driver = baseCommon.getDriver();
        	driver.get(url);
            String userName = userNames.get(i);
            try{
                // 如果过程中发生异常，则关掉浏览器重新启动
                if(baseCommon.getDriver() == null)
                {
                    baseCommon = new BaseCommon();
                    driver = baseCommon.getDriver();
                    driver.get(url);
                }
                baseCommon.invokeMethod(driver.findElement(By.name("username000")), CLEAR_METHOD);
                baseCommon.invokeMethod(driver.findElement(By.name("username000")), SEND_KEYS_METHOD, userName);
                driver.findElement(By.name("username000")).sendKeys(Keys.TAB);
                Thread.currentThread().sleep(100);
                WebElement selectOrg = driver.findElement(By.name("username1"));
                if(selectOrg != null && selectOrg.isDisplayed())
                {
                    //Select select = new Select(selectOrg);
                    //select.selectByIndex(1);
                    System.out.println(userName + "存在多个角色信息");
                }
                baseCommon.invokeMethod(driver.findElement(By.name("password")), CLEAR_METHOD);
                baseCommon.invokeMethod(driver.findElement(By.name("password")), SEND_KEYS_METHOD, "8888");
                baseCommon.invokeMethod(driver.findElement(By.cssSelector("a")), CLICK_METHOD);
                Thread.currentThread().sleep(100);
                //退出
                driver.get(logoutUrl);
                baseCommon.closeBrowser();
            }catch (Exception e){
                System.err.println(userName + "登陆失败");
            }
        }
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
                    "username from gw_ams_user where status <>0");
            while(rs.next())
            {
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
