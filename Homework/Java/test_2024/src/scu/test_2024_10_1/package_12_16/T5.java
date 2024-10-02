package scu.test_2024_10_1.package_12_16;

import java.util.Scanner;

public class T5 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int[][] arr = new int[5][5];
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                arr[i][j] = input.nextInt();
            }
        }
        int n = input.nextInt() - 1, m = input.nextInt() - 1;
        for (int j = 0; j < 5; ++j) {
            int temp = arr[n][j];
            arr[n][j] = arr[m][j];
            arr[m][j] = temp;
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
