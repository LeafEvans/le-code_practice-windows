package scu.test_2024_10_3.package_14_50;

// 一个类文件中只能有一个 public 修饰的类

import java.util.Scanner;

class AgeException extends Exception {
    public AgeException(String msg) {
        super(msg);
    }
}

public class Main {
    public static void main(String[] args) {
        // 自定义异常
        // 登记用户的姓名和年龄，若年龄不合法，给出提示
        Scanner input = new Scanner(System.in);
        System.out.println("请输入姓名：");
        String name = input.next();
        System.out.println("请输入年龄：");
        try {
            int age = input.nextInt();
            if (age < 0) {
                throw new AgeException("年龄不能为负数");
            }
            System.out.println("姓名：" + name);
            System.out.println("年龄：" + age);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
