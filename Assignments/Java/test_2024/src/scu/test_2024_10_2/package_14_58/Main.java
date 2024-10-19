package scu.test_2024_10_2.package_14_58;

public class Main {
    public static void main(String[] args) {
        Dance[] dances = new Dance[] {new Dancer(), new DanceTeacher()};
        for (var dance : dances) {
            dance.dance();
        }
    }
}
