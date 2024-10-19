package scu.test_2024_10_2.package_16_55;

public class Main {
    public static void main(String[] args) {
        PrintMachine[] printMachines = {new InkjetPrinter(), new LaserPrinter(), new NeedlePrinter()};

        for (var printMachine : printMachines) {
            printMachine.show();
            printMachine.print();
            System.out.println();
        }
    }
}
