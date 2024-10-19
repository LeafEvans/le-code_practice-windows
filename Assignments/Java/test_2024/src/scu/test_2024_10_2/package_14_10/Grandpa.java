package scu.test_2024_10_2.package_14_10;

public class Grandpa {
    public Animal blowSugarAnimal(String type) {
        Animal animal;
        if (type.equals("dog")) {
            animal = new Dog();
        } else if (type.equals("cat")) {
            animal = new Cat();
        } else {
            animal = new Pig();
        }
        return animal;
    }
}
