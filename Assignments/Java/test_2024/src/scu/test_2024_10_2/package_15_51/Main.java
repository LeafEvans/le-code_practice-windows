package scu.test_2024_10_2.package_15_51;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("请输入第一个操作数:");
        Scanner input = new Scanner(System.in);
        int n1 = input.nextInt();
        System.out.println("请输入第二个操作数");
        int n2 = input.nextInt();
        Calculator[] calculators = { new AddCalculator(), new SubCalculator(),
                new MulCalculator(), new DivCalculator() };

        for (var calc : calculators) {
            System.out.println(calc.calc(n1, n2));
        }

        input.close(); 
    }
}
