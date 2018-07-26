function Login
        ret
function test
        j = Int:10;
        goto BB1;
BB0:
        j = j + Int:1;
BB1:
        if (j < Int:100) goto BB0;
        Login();
        ret

