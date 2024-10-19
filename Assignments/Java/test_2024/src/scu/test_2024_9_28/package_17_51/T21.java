package scu.test_2024_9_28.package_17_51; // 指定包名

import java.util.Scanner; // 导入 Scanner 类用于输入

public class T21 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in); // 创建 Scanner 对象以获取用户输入
        boolean flag = true; // 控制循环的标志，初始为 true
        int money = 0, sum = 0, num = 0; // 初始化变量：money（当前消费金额），sum（总销售额），num（顾客总数）

        // 外层循环，用于处理每位顾客的购物
        while (flag) {
            int sum_one = 0; // 初始化当前顾客的购物金额
            do {
                money = input.nextInt(); // 读取用户输入的金额

                if (money == -1) { // 检查是否输入-1，表示结束输入
                    flag = false; // 将标志改为 false，退出循环
                    break; // 退出 do-while 循环
                }

                sum_one += money; // 将当前输入的金额累加到 sum_one
            } while (money != 0); // 当用户输入的金额不为 0 时继续循环，0 表示该顾客结束购物

            sum += sum_one; // 将当前顾客的购物金额加到总销售额
            ++num; // 顾客数量加 1
            System.out.println("您的购物金额为：" + sum_one); // 输出当前顾客的购物金额
        }

        // 输出今日顾客总数和总销售额
        System.out.println("今日顾客总数为：" + num);
        System.out.println("总销售额：" + sum);

        input.close(); // 关闭 Scanner 对象以释放资源
    }
}
