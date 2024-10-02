package scu.test_2024_9_28.package_17_51;

import java.util.Scanner;

public class T23 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int total = 0;
        for (int i = 1; i <= n; ++i) {
            int temp = i;
            while (temp != 0) {
                int bit = temp % 10;
                if (bit == 1) {
                    ++total;
                }
                temp /= 10;
            }
        }
        System.out.println(total);
        input.close();
    }
}
