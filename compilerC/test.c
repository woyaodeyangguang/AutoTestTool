public void Login(String passwd) {
}
public void expectToSeeLinkText(String p) {
}
public void fillCreateUserForm(String userId, String userName, String department, String phone, String email, String snapshot) {
  expectToSeeLinkText ("user");
}
public void testCreateSuperuserRight(String userId, String userName, String department, String phone, String email, String snapshot) {
  String url="http://192.168.101.131:8080/private-cloud/login", inputUsernameId="realNameText", adminName="张超", selectRoleId="usernameSelect", select="chaochao", inputPasswordId="password", password="12345", submitBtnId="loginbtn", logoutId="logoutLink";
  fillCreateUserForm (userId , userName , department , phone , email , snapshot );
}
public void test(String mypa) {
  String mypa, b=90 ;
  for(j =10 j <100 ;j =j +1 ) {
    Login ("人");
    Login (mypa );
  }
  Login (b );
  fillCreateUserForm ("zhangsan", "ab", "it", "123", "12", "");
}

