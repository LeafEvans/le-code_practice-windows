package scu.test_2024_10_2.package_13_05;

public class Cat extends Pet {
    public Cat() {
    }

    public Cat(String name, int power) {
        this.name = name;
        this.power = power;
    }

    @Override
    public void eat(int num) {
        this.power += num;
        System.out.println("猫" + this.name
                + "能量值增加了" + num
                + "，最终的能力值为：" + this.power);
    }
}
