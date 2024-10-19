package scu.test_2024_10_3.package_22_42;

import java.util.Scanner;

public class Main {
    public static int fbi(int n) {
        if (n == 1 || n == 2) {
            return 1;
        }
        return fbi(n - 1) + fbi(n - 2);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println(fbi(sc.nextInt()));
        sc.close();
    }
}
