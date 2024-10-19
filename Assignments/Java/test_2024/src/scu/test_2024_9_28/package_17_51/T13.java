package scu.test_2024_9_28.package_17_51;

import java.util.Scanner;

public class T13 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int num = input.nextInt();
        if (num % 2 == 0) {
            System.out.println("偶数");
        } else {
            System.out.println("奇数");
        }
        input.close();
    }
}
