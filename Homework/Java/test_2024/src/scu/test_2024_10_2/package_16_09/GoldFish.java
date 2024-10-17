package scu.test_2024_10_2.package_16_09;

public class GoldFish extends Fish {
    public GoldFish() {
    }

    public GoldFish(String type) {
        this.type = type;
    }

    @Override
    public void eat() {
        System.out.println("金鱼吃东西");
    }

    @Override
    public void show() {
        System.out.println("类型为" + type);
    }

    @Override
    public void swim() {
        System.out.println("金鱼在游泳");
    }

}
