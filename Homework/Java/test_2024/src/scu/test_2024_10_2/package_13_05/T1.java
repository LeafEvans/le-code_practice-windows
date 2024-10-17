package scu.test_2024_10_2.package_13_05;

public class T1 {
    public static void main(String[] args) {
        Dog dog = new Dog("可乐", 100);
        Cat cat = new Cat("雪碧", 100);
        Master master = new Master();
        master.feed(dog, 30);
        master.feed(cat, 30);
    }
}
