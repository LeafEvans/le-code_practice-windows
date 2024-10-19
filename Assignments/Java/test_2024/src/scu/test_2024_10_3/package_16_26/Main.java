package scu.test_2024_10_3.package_16_26;

import java.util.Scanner;

public class Main {
    public static int fib(int n) {
        if (n == 1 || n == 2) {
            return 1;
        }

        int a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            int c = a + b;
            a = b;
            b = c;
        }
        return b;
    }

    public static void main(String[] args) {
        Test test = new Test();
        test.num = 1;
        System.out.println(fib(test.num));
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(fib(n));
        sc.close();
    }
}
