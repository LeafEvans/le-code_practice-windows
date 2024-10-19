package scu.test_2024_10_1.package_0_06;

import java.util.Scanner;

public class T4 {
    public static void main(String[] args) {
        System.out.print("请输入一个数字，范围是 1 ~ 100 之间，包含边界：");
        Scanner input = new Scanner(System.in);
        int num = input.nextInt(), left = 1, right = 100;
        while (left < right) {
            int mid = (left + right) >> 1;
            if (mid >= num) {
                right = num;
            } else {
                left = mid + 1;
            }
        }
        System.out.println(left);
        input.close();
    }
}
