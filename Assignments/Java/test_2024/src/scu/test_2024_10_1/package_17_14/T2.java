package scu.test_2024_10_1.package_17_14;

import java.util.Scanner;

public class T2 {

    public static int func(int n) {
        return n == 1 ? 1 : n * func(n - 1);
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        System.out.println(func(n));
        input.close();
    }

}
