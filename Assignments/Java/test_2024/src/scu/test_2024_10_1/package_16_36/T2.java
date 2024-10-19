package scu.test_2024_10_1.package_16_36;

import java.util.Scanner;

public class T2 {
    public static void main(String[] args) {
        int[] scores = new int[5];
        Calc calc = new Calc();
        Scanner input = new Scanner(System.in);
        System.out.println("请输入 5 名学员的成绩：");
        for (int i = 0; i < scores.length; ++i) {
            scores[i] = input.nextInt();
        }
        System.out.println("总分为：" + calc.getTotal(scores));
        System.out.println("平均分为：" + calc.getAvgScore(scores));
        System.out.println("最高分为：" + calc.getMaxScore(scores));
        input.close();
    }
}
