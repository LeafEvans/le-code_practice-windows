package scu.test_2024_10_2.package_16_09;

public class Shark extends Fish implements Power {

    public Shark() {
    }

    public Shark(String type) {
        this.type = type;
    }

    @Override
    public void eat() {
        System.out.println("鲨鱼吃东西");
    }

    @Override
    public void show() {
        System.out.println("类型为" + this.type);
    }

    @Override
    public void swim() {
        System.out.println("鲨鱼在游泳");
    }

    @Override
    public void power() {
        System.out.println("鲨鱼进行电感应");
    }

}
