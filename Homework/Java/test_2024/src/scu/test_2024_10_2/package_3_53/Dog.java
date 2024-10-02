package scu.test_2024_10_2.package_3_53;

public class Dog {
    private String name;

    private int age;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age < 0 ? 0 : age;
    }
}
