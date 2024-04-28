public class Main {
    public static void main(String[] args) {
        System.out.println("Hello World!");
        int[] Array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int[] Array2 = new int[10];
        for (int i : Array) {
            if (i % 2 == 0) {
                System.out.println(i);
            }
        }
    }
}
