package scu.test_2024_10_2.package_16_09;

public class Main {
    public static void main(String[] args) {
        Fish[] fishes = { new GoldFish("金鱼"), new Shark("鲨鱼") };
        for (Fish fish : fishes) {
            fish.eat();
            fish.swim();
            if (fish instanceof Shark) {
                ((Shark) fish).power();
            }
            fish.show();
            System.out.println();
        }
    }
}
