package scu.test_2024_10_1.package_12_16;

import java.util.Scanner;

public class T1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int[][] arr = new int[n + 1][n + 1];
        for (int i = 1; i <= (n + 1) >> 1; ++i) {
            for (int j = 1; j <= (n + 1) >> 1; ++j) {
                arr[i][j] = Math.min(i, j);
                arr[i][n + 1 - j] = Math.min(i, j);
                arr[n + 1 - i][j] = Math.min(i, j);
                arr[n + 1 - i][n + 1 - j] = Math.min(i, j);
            }
        }
        input.close();
    }
}
