package scu.test_2024_10_1.package_12_16;

import java.util.Scanner;

public class T8 {
    public static void main(String[] args) {
        UserInfo[] users = new UserInfo[50];
        UserInfo info = new UserInfo();
        info.username = "LeafEvans";
        info.password = "12345678";
        users[0] = info;

        Scanner input = new Scanner(System.in);
        System.out.print("请输入用户名：");
        String username = input.next();
        System.out.println("请输入密码：");
        String password = input.next();

        boolean flag = false;

        for (int i = 0; i < users.length; ++i) {
            if (users[i] != null
                    && users[i].username.equals(username)
                    && users[i].password.equals(password)) {
                flag = true;
                break;
            }
        }
        if (flag == true) {
            System.out.println("登录成功");
        } else {
            System.out.println("登录失败");
        }
        input.close();
    }
}
