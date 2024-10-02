package scu.test_2024_10_1.package_0_06;

import java.util.Scanner;

public class T2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int[] arr = new int[6];
        for (int i = 0; i < arr.length - 1; ++i) {
            arr[i] = input.nextInt();
        }
        int num = input.nextInt();
        int index = arr.length - 1;
        for (int i = 0; i < arr.length; ++i) {
            if (num < arr[i]) {
                index = i;
                break;
            }
        }
        for (int i = arr.length - 1; i > index; --i) {
            arr[i] = arr[i - 1];
        }
        arr[index] = num;
        for (int i = 0; i < arr.length; ++i) {
            System.out.print(arr[i] + " ");
        }
        input.close();
    }
}
