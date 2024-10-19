package scu.test_2024_10_2.package_13_05;

public class Dog extends Pet {
    public Dog() {

    }

    public Dog(String name, int power) {
        this.name = name;
        this.power = power;
    }

    @Override
    public void eat(int num) {
        this.power += num;
        System.out.println("狗" + this.name
                + "能量值增加了" + num
                + "，最终的能量值为：" + this.power);
    }
}
