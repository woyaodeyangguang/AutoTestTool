int i, j, k, useridList.length, userList.length
//int i, useridList.length;
void disable_user(useridList, id)
{
    /*
    Expected_to_see_linktext("用户管理");
    Click_link("用户管理");
    */

    for(i=0; i<useridList.length; ++i){    //click_checkbox(user_id);
    click("id", i); //useridList[i]);
    click("id", id);
}
click("id", "openDisableUserDialogButton");
}
void test() {
char* userList[] =  {"张超", "zhangchao", "Yun"};
disable_user(userList);
}
/*
//%% test1: good case
Login(url, "张超","zhangchao","12345");
disable_user(["chaochao", "wangyun"]);
Expected_to_see("id", "confirmationButton");
Click("id", "confirmationButton");
//%%  检查是否此人对应的状态变为“停用”
disable_user(["chaochao"]);
Expected_not_to_see("id", "confirmationButton");
Logout();
//% 检查是否可重新登录
Login(url, "张超", "chaochao", "12345");
Expected_to_see("text", "当前用户没有可用的角色");
Login(url, "王云", "wangyun", "12345");
Expected_to_see("text", "当前用户没有可用的角色");


//%% test2: 停用账号+启用账号
Login(url, "张超","zhangchao","12345");
disable_user(["chaochao", "小德平"]);
Expected_not_to_see("confirmationButton", "id");
Logout();

//%% test3: 注销账号
Login(url, "张超","zhangchao","12345");
disable_user(["someone"]);
Expected_not_to_see("id", "confirmationButton");
Logout();

//%% test4: 注销账号+启用账号
Login(url, "张超","zhangchao","12345");
disable_user(["chaochao", "someone"]);
Expected_not_to_see("id", "confirmationButton");
Logout();

//%% test5: 需要多用户同时登录，当前系统暂不支持
//%% 选取一个已启用帐户，同时登录一个已启用帐户。停用此帐户。然后已登录帐户点击页面上所有可点击的按钮，检查错误提示。
*/
