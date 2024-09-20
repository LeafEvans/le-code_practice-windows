import java.util.Scanner;

public class CalenderDisplay {
    static int[] daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    static String[] months = {
            "January", "February", "March", "April", "May", "June",
            "July", "Augest", "September", "October", "November", "December"
    };

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("请输入年份: ");
        int year = scanner.nextInt();
        System.out.print("请输入该年第一天是星期几 (0表示星期天, 1表示星期一, ..., 6表示星期六): ");
        int startDay = scanner.nextInt();

        if (isLeapYear(year)) {
            daysInMonth[1] = 29;
        }

        for (int month = 0; month < 12; ++month) {
            System.out.println("          " + months[month] + " " + year);
            System.out.println(" Sun Mon Tue Wed Thu Fri Sat");

            for (int i = 0; i < startDay; ++i) {
                System.out.print("    ");
            }

            for (int day = 1; day <= daysInMonth[month]; ++day) {
                System.out.printf("%4d", day);

                if ((day + startDay) % 7 == 0) {
                    System.out.println();
                }
            }

            startDay = (startDay + daysInMonth[month]) % 7;
            System.out.println();
        }

        scanner.close();
    }

    public static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) && (year % 400 == 0);
    }
}