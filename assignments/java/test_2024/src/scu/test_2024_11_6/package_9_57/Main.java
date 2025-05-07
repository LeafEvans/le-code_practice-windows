package scu.test_2024_11_6.package_9_57;

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

        quickSort(arr, left, j);
        quickSort(arr, j + 1, right);
    }

    public static void mergeSort(int[] arr, int left, int right) {
        if (left >= right) {
            return;
        }

        int mid = left + right >> 1;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        int k = 0, i = left, j = mid + 1;

        int[] temp = new int[right - left + 1];

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        while (j <= right) {
            temp[k++] = arr[j++];
        }

        for (i = left, j = 0; i < right; ++i, ++j) {
            arr[i] = temp[j];
        }
    }

    public static void main(String[] args) {

    }
}
