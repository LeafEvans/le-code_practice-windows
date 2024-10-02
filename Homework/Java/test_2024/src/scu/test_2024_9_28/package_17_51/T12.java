package scu.test_2024_9_28.package_17_51;

import java.util.Scanner;

public class T12 {
    public static void main(String[] args) {
        // 成绩判定
        // 01. 接受用户从键盘上输入的成绩
        Scanner input = new Scanner(System.in);
        int score = input.nextInt();
        // 02. 判断成绩和 96 的关系
        if (score > 96) {
            // 03. 输出结果
            System.out.println("得到🏀作为奖励");
        }
        input.close();
    }
}
