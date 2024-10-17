package scu.test_2024_10_2.package_13_52;

public class Main {
    public static void main(String[] args) {
        Chinese chinese = new Chinese();
        American american = new American();
        Korean korean = new Korean();
        Person[] persons = new Person[3];
        persons[0] = chinese;
        persons[1] = american;
        persons[2] = korean;

        for (Person person : persons) {
            person.sayHello();
        }
    }
}
