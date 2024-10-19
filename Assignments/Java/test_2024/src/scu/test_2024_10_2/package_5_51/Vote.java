package scu.test_2024_10_2.package_5_51;

public class Vote {
    // 投票次数
    static int count;

    // 投票最大次数
    public static final int MAX_COUNT = 1000;

    // 投票人名字
    public String name;

    public Vote() {
    }

    public Vote(String name) {
        this.name = name;
    }

    // 投票方法
    public void vote() {
        if (count == MAX_COUNT) {
            System.out.println("活动已经结束");
        } else {
            ++count;
            System.out.println("感谢" + name + "投票");
        }
    }

    public static void show() {
        System.out.println("目前" + count + "票");
    }
}
