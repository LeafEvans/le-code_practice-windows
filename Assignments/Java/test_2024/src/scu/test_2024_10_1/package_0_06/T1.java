package scu.test_2024_10_1.package_0_06;

import java.util.Scanner;
import java.util.Arrays;

public class T1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int[] a = new int[10];
        for (int i = 0; i < a.length; ++i) {
            a[i] = input.nextInt();
        }
        Arrays.sort(a);
        for (int i = 0; i < a.length; ++i) {
            System.out.print(a[i] + " ");
        }
        input.close();
    }
}