package scu.test_2024_10_2.package_15_51;

public class DivCalculator implements Calculator {
    @Override
    public double calc(int n1, int n2) {
        return n2 == 0 ? 0 : n1 * 1.0 / n2;
    }
}
