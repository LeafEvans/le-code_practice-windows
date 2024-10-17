package scu.test_2024_10_3.package_12_34;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        try {
            System.out.println("Enter n1: ");
            int n1 = input.nextInt();
            System.out.println("Enter n2: ");
            int n2 = input.nextInt();
            int res = n1 / n2;
            System.out.println(res);
        } catch (InputMismatchException ex) {
            System.out.println("被除数和除数都必须是整数");
        } catch (ArithmeticException ex) {
            System.out.println("除数不能为 0");
        } catch (Exception ex) {
            System.out.println("未知异常");
        } finally {
            System.out.println("程序结束");
        }
    }
}
