package scu.test_2024_9_28.package_17_51;

public class T10 {
    public static void main(String[] args) {
        int num = 123;
        int bit1 = num % 10;
        int bit2 = num / 10 % 10;
        int bit3 = num / 100;
        System.out.println("个位为："+bit1);
        System.out.println("十位为："+bit2);
        System.out.println("百位为："+bit3);
    }
}
