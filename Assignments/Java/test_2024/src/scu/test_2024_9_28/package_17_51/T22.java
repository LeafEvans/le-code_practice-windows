package scu.test_2024_9_28.package_17_51;

import java.util.Scanner;

public class T22 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int total = 0;

        for (int i = 1; i <= n; ++i) {
            int temp = 1;
            for (int j = 1; j <= i; ++j) {
                temp *= j;
            }
            total += temp;
        }

        System.out.println(total);

        input.close();
    }
}
