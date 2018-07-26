package com.sinosoft.selenium;
import org.junit.Test;
public class create_user_sample {
BaseCommon base = new BaseCommon();
public void fillCreateUserForm(String userId, String userName, String department, String phone, String email, String snapshot) {
base.expectToSeeLinkText("用户管理");
base.clickLink("用户管理");
base.expectToSee("id", "openAddUserDialogButton");
base.click("id", "openAddUserDialogButton");
base.feedTextBox("id", "addUserUsernameText", userId);
base.selectDropBox("id", "addUserRoleSelect", "ROLE_ADMIN");
base.feedTextBox("id", "addUserRealNameText", userName);
base.feedTextBox("id", "addUserDepartmentText", department);
base.feedTextBox("id", "addUserPhoneText", phone);
base.feedTextBox("id", "addUserEmailText", email);
base.feedTextBox("id", "addUserSnapshotQuotaText", snapshot);
base.click("text", "确定");
}
public void testCreateSuperuserRight(String userId, String userName, String department, String phone, String email, String snapshot) {
String url="http://192.168.101.131:8080/private-cloud/login";
String inputUsernameId="realNameText";
String adminName="张超";
String selectRoleId="usernameSelect";
String select="chaochao";
String inputPasswordId="password";
String password="12345";
String submitBtnId="loginbtn";
String logoutId="logoutLink";
base.login(url, inputUsernameId, adminName, selectRoleId, select, inputPasswordId, password, submitBtnId);
fillCreateUserForm(userId, userName, department, phone, email, snapshot);
base.expectToSeeLinkText(userId);
base.logout(logoutId);
base.login(url, inputUsernameId, userName, selectRoleId, select, inputPasswordId, password, submitBtnId);
base.expectToSeeLinkText("域组管理");
base.logout(logoutId);
}
@Test
public void Test1() {
testCreateSuperuserRight("zhangsan", "张三", "it", "123", "qq", "qq");
}
@Test
public void Test2() {
testCreateSuperuserRight("zhangsi", "张三", "it", "123", "234@qq.com", "qq");
}
}
