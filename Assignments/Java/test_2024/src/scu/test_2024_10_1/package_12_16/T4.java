package scu.test_2024_10_1.package_12_16;

import java.util.Scanner;

public class T4 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int m = input.nextInt();
        int[][] arr = new int[n][m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                arr[i][j] = input.nextInt();
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                System.out.print(arr[n - 1 - j][i] + " ");
            }
            System.out.println();
        }
        input.close();
    }
}
