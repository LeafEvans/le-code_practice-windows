package scu.test_2024_10_2.package_5_51;

public class T1 {
    public static void main(String[] args) {
        Vote vote = new Vote("张三");
        Vote vote2 = new Vote("李四");
        Vote.show();
        vote.vote();
        Vote.show();
        vote2.vote();
        Vote.show();
    }
}
