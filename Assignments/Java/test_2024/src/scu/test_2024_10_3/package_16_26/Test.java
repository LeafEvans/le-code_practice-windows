package scu.test_2024_10_3.package_16_26;

public class Test {
    int num;

    @Override
    public String toString() {
        return "Test{" +
                "num=" + num +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof Test && num == ((Test) obj).num;
    }
}
