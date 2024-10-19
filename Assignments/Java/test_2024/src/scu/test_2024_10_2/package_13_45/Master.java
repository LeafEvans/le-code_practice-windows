package scu.test_2024_10_2.package_13_45;

public class Master {
    public void feed(Pet pet, int num) {
        pet.eat(num);
    }

    public void work(Pet pet) {
        if (pet instanceof Cat) {
            ((Cat) pet).catchMouse();
        } else if (pet instanceof Dog) {
            ((Dog) pet).seeDoor();
        }
    }
}
