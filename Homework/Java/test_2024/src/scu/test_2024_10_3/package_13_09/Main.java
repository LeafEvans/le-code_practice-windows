package scu.test_2024_10_3.package_13_09;

public class Main {
    public static void test() throws Exception {
        System.out.println(5 / 0);
    }

    public static void main(String[] args) {
        try {
            test();
        } catch (Exception e) {
            System.out.println("除数不能为零");
        }
    }
}
