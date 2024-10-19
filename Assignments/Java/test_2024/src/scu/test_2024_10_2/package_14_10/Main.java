package scu.test_2024_10_2.package_14_10;

public class Main {
    public static void main(String[] args) {
        var grandpa = new Grandpa();
        String[] types = { "dog", "cat", "pig" };
        for (var type : types) {
            var animal = grandpa.blowSugarAnimal(type);
            animal.getShape();
        }
    }
}
