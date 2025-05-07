package scu.test_2024_11_6.package_13_13;

import java.util.Arrays;

public class Main {
    public static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void quickSort(int[] arr, int left, int right) {
        if (left >= right) {
            return;
        }

        int x = arr[left];
        int i = left - 1, j = right + 1;

        while (i < j) {
            do {
                ++i;
            } while (arr[i] < x);

            do {
                --j;
            } while (arr[j] > x);

            if (i < j) {
                swap(arr, i, j);
            }
        }
        quickSort(arr, 0, arr.length - 1);
        System.out.println(Arrays.toString(arr));
    }
}
