package scu.test_2024_10_1.package_15_47;

import java.util.Scanner;

public class T1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Calc calc = new Calc();
        System.out.println("请输入语文成绩：");
        calc.chinese = input.nextInt();
        System.out.println("请输入数学成绩：");
        calc.math = input.nextInt();
        System.out.println("请输入英语成绩：");
        calc.english = input.nextInt();
        int total = calc.getTotal();
        double avgScore = calc.getAvgScore();
        System.out.println("总分为：" + total);
        System.out.println("平均分为：" + String.format("%.2f", avgScore));
        input.close();
    }

}
