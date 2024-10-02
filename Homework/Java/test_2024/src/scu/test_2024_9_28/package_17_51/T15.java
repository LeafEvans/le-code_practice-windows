package scu.test_2024_9_28.package_17_51;

import java.util.Scanner;

public class T15 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int num = input.nextInt();
        if (num % 400 == 0 || (num % 4 ==0 && num % 100 != 0)) {
            System.out.println(num + " 是闰年。");
        }
        input.close();
    }
}
