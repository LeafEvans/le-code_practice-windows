package scu.test_2024_9_28.package_17_51;

import java.util.Scanner;

public class T14 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int day = input.nextInt();
        switch (day) {
            case 1:
                System.out.println("红烧肉");
                break;
            case 2:
                System.out.println("土豆牛肉");
                break;
            case 3:
                System.out.println("炸鸡");
                break;
            case 4:
                System.out.println("汉堡");
                break;
            case 5:
                System.out.println("白菜豆腐");
                break;
            default:
                System.out.println("今日未提供菜品");
                break;
        }
        input.close();
    }
}
