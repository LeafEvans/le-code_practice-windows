package scu.test_2024_10_2.package_11_10;

public class Cat extends Animal {
    public void show() {
        super.age = 10;
    }

    public Cat() {
        super(2);
        System.out.println("Cat 构造");
    }
}
