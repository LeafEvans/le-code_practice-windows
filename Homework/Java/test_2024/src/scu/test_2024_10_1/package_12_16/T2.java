package scu.test_2024_10_1.package_12_16;

import java.util.Scanner;

public class T2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt(), t = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                System.out.print(t++ + " ");
            }
            System.out.println();
        }
        input.close();
    }
}
