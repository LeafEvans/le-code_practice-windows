package scu.test_2024_10_1.package_12_16;

import java.util.Scanner;

public class T3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int[][] arr = new int[10][10];
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                arr[i][j] = input.nextInt();
                arr[i][j] = (i == j || i + j == 4) ? arr[i][j] + 10 : arr[i][j];
            }
        }
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                System.out.print(arr[i][j] + "\t");
            }
            System.out.println();
        }

        input.close();
    }
}
