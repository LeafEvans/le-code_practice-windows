package scu.test_2024_10_1.package_15_47;

public class Calc {
    int chinese;
    int math;
    int english;
    public int getTotal() {
        int totalSocre = chinese + math + english;
        return totalSocre;
    }
    public double getAvgScore() {
        double avgScore = getTotal() / 3;
        return avgScore;
    }
}
