package scu.test_2024_10_1.package_16_36;

public class Calc {
    public int add(int num1, int num2) {
        return num1 + num2;
    }

    public double getAvgScore(int[] scores) {
        return getTotal(scores) / scores.length;
    }

    public int getTotal(int[] scores) {
        int total = 0;
        for (int i = 0; i < scores.length; ++i) {
            total += scores[i];
        }
        return total;
    }

    public int getMaxScore(int[] scores) {
        int max = scores[0];
        for (int i = 1; i < scores.length; ++i) {
            if (scores[i] > max) {
                max = scores[i];
            }
        }
        return max;
    }
}
