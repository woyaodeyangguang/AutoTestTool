void Login(passwd) {

}
int j;

void expectToSeeLinkText(p) {
}
void fillCreateUserForm( userId,  userName,  department,  phone,  email,  snapshot)
{
  expectToSeeLinkText("user");//用户管理");
	/*
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
	click("text", "确定");*/
}
void testCreateSuperuserRight(userId, userName, department, phone, email, snapshot)
{
	char* url = "http://192.168.101.131:8080/private-cloud/login";

    char* inputUsernameId = "realNameText";
    char* adminName = "张超";
    char* selectRoleId = "usernameSelect";
    char* select = "chaochao";

    char* inputPasswordId = "password";

    char* password[2] = {"12345","22"};
    String submitBtnId = "loginbtn";
    String logoutId = "logoutLink";
  
	//    login(url, inputUsernameId, adminName, selectRoleId, select, inputPasswordId, password, submitBtnId);
	fillCreateUserForm(userId, userName, department, phone, email, snapshot);
	/*
	expectToSeeLinkText(userId);
	logout(logoutId);

	login(url, inputUsernameId, userName, selectRoleId, select, inputPasswordId, password, submitBtnId);
	expectToSeeLinkText("域组管理");
	logout(logoutId);
	*/
}
void test(mypa) {
     char mypa,b=90; 
	//int j;
     for (j=10;j<100;j+=1) {
	Login("人");
	Login(mypa);	
	}
     Login(b);

      fillCreateUserForm("zhangsan", "ab", "it", "123", "12", "");

}
/*
public void testLogin(){
        String url = "http://192.168.100.11:8088/private-cloud/login";
        String inputUsernameId = "realNameText";
        String username = "超级管理员";
        String selectRoleId = "usernameSelect";
        String inputPasswordId = "password";
        String password = "12345";
        String submitBtnId = "loginbtn";
        base.login(url, inputUsernameId, username, selectRoleId, inputPasswordId,
                password, submitBtnId);
        //base.closeBrowser();
        //base.logout("logoutLink", "logoutButton");
        base.logout("logoutLink");
        base.logout("logoutLink", "logoutButton");
    }
void testLogin() {
	Login("chaochao", "guanliyuan", "12345");
}
*/
