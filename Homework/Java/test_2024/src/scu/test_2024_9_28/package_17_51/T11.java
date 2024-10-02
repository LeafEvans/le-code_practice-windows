package scu.test_2024_9_28.package_17_51;

import java.util.Scanner;

public class T11 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        char ch = input.next().charAt(0);
        char bigCh = (char) (ch - 32);
        System.out.println(bigCh);
        input.close();
    }
}
