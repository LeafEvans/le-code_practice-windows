package scu.test_2024_10_3.package_13_35;

public class Main {
    public static void divide(int a, int b) {
        if (b == 0) {
            throw new ArithmeticException("除数不能为零");
        }

        System.out.println("结果为：" + a / b);

    }

    public static void main(String[] args) {
        try {
            divide(4, 0);
        } catch (ArithmeticException e) {
            System.out.println(e.getMessage());
        }
    }
}
