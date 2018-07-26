void Login(passwd) {
}
int j;
/*
void fillCreateUserForm(userId, userName, department,  phone,  email,  snapshot)
{
  expectToSeeLinkText("user");//用户管理");
	
	clickLink("用户管理");
	expectToSee("id", "openAddUserDialogButton");
	click("id", "openAddUserDialogButton");
	feedTextBox("id", "addUserUsernameText", user_id);
	selectDropBox("id", "addUserRoleSelect", "ROLE_ADMIN");
	feedTextBox("id", "addUserRealNameText", user_name);
	feedTextBox("id", "addUserDepartmentText", department);
	feedTextBox("id", "addUserPhoneText", phone);
	feedTextBox("id", "addUserEmailText", email);
	feedTextBox("id", "addUserSnapshotQuotaText", snapshot);
	click("text", "确定");
}

void testCreateSuperuserRight(userId, userName, department, phone, email, snapshot)
{
  
  url = "http://192.168.101.131:8080/private-cloud/login";
  inputUsernameId = "realNameText";
  adminName = "张超";
  selectRoleId = "usernameSelect";
  select = "chaochao";
  inputPasswordId = "password";
  password = "12345";
  submitBtnId = "loginbtn";
  logoutId = "logoutLink";
  
	//    login(url, inputUsernameId, adminName, selectRoleId, select, inputPasswordId, password, submitBtnId);
  fillCreateUserForm(userId, userName, department, phone, email, snapshot);

	expectToSeeLinkText(userId);
	logout(logoutId);

	login(url, inputUsernameId, userName, selectRoleId, select, inputPasswordId, password, submitBtnId);
	expectToSeeLinkText("域组管理");
	logout(logoutId);

}

void test{
// good cases
testCreateSuperuserRight("zhangsan", "张三", "it", "123", "", "");
testCreateSuperuserRight("zhangsi", "张三", "it", "123", "234@qq.com", "");
}
*/