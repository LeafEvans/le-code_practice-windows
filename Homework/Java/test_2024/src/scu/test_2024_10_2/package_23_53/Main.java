package scu.test_2024_10_2.package_23_53;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("Enter n1: ");
        int n1 = input.nextInt();
        System.out.println("Enter n2: ");
        int n2 = input.nextInt();
        try {
            int res = n1 / n2;
            System.out.println(res);
        } catch (Exception ex) {
            System.err.println("除数不能为 0");
            ex.printStackTrace();
            System.out.println(ex.getMessage());
            return;
        } finally {
            System.out.println("程序结束");
        }
    }
}
