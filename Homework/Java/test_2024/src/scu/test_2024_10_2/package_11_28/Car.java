package scu.test_2024_10_2.package_11_28;

public class Car {
    public String brand;

    public String color;

    public int money;

    public Car(String brand, String color, int money) {
        this.brand = brand;
        this.color = color;
        this.money = money;
    }

    @Override
    public String toString() {
        return "Car{" +
                "brand='" + brand + '\'' +
                ", color='" + color + '\'' +
                ", money=" + money +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Car) {
            return brand.equals(((Car) obj).brand);
        } else {
            return false;
        }
    }

}
