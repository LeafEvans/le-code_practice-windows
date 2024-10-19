package scu.test_2024_10_1.package_17_14;

public class Dog {
    // 属性
    public String brand;
    public String name;
    public int age;

    // 无参构造方法
    public Dog() {
        System.out.println("Dog");
    }

    // 有参构造函数
    public Dog(String brand, String name, int age) {
        this.brand = brand;
        this.name = name;
        this.age = age;
    }

    // 方法
    public void run() {
        System.out.println("run");
    }

    public void bark() {
        System.out.println("bark");
    }

    public void show() {
        System.out.println("品种是：" + brand
                + "，姓名是：" + name
                + "，年龄为：" + age);
    }
}
