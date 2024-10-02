package scu.test_2024_10_2.package_3_08;

public class StaticTest {
    static int num = 100;
    
    static {
        num += 100;
        System.out.println(num);
    }

    static {
        num += 500;
        System.out.println(num);
    }
}
