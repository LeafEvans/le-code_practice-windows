package scu.test_2024_10_3.package_22_42;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        for (int i = 0; i < 10; ++i) {
            System.out.println("Enter number " + i + ":");
            for (int j = 0; j < 10; ++j) {
                System.out.println("Enter number " + j + ":");
            }
        }
        sc.close();
    }
}
