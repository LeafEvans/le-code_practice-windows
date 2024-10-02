package scu.test_2024_10_1.package_17_14;

public class T3 {
    public static void main(String[] args) {
        Dog dog = new Dog();
        dog.brand = "拉布拉多";
        dog.name = "小黑子";
        dog.age = 5;
        dog.show();

        Dog dog2 = new Dog("边牧", "ikun", 2);
        dog2.show();
    }
}
