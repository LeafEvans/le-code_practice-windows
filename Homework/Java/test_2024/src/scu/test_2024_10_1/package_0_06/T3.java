package scu.test_2024_10_1.package_0_06;

import java.util.Scanner;

public class T3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int[] arr = new int[101];
        int n = input.nextInt();
        for (int i = 1; i <= n; ++i) {
            arr[i] = input.nextInt();
        }
        int index = input.nextInt();
        for (int i = index; i <= n; ++i) {
            arr[i] = arr[i + 1];
        }
        --n;
        for (int i = 1; i <= n; ++i) {
            System.out.print(arr[i] + " ");
        }
        input.close();
    }
}