package scu.test_2024_9_28.package_17_51;

public class T20 {
    public static void main(String[] args) {
        for (int i = 1; i <= 33; ++i) {
            for (int j = 1; j <= 50; ++j) {
                for (int k = 1; k <= 98; ++k) { 
                    if (i + j + k == 100 && 3 * i + 2 * j + k / 3.0 == 100) {
                        System.out.println(i + "\t" + j + "\t" + k);
                    }
                }
            }
        }
    }
}
