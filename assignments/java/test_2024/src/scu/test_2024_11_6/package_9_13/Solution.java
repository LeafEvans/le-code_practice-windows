package scu.test_2024_11_6.package_9_13;

import java.util.Scanner;

public class Solution {

    private static class Account {
        private double balance;
        private double annualInterestRate;

        public Account(int id, double annualInterestRate) {
            this.annualInterestRate = annualInterestRate;
            this.balance = 0.0;
        }

        public void withdraw(double amount) {
            if (amount <= balance) {
                balance -= amount;
            }
        }

        public void deposit(double amount) {
            balance += amount;
        }

        public void addDailyInterest(int days) {
            double dailyInterestRate = annualInterestRate / 365;
            for (int i = 0; i < days; i++) {
                balance += balance * dailyInterestRate;
            }
        }

        public double getBalance() {
            return Math.round(balance * 100.0) / 100.0;
        }
    }

    public void execute() {
        Scanner in = new Scanner(System.in);

        Account account = new Account(1, 0.05);

        int n = in.nextInt();

        for (int i = 0; i < n; i++) {
            int operation = in.nextInt();
            double amountOrDays = 0.0;

            switch (operation) {
                case 0:
                    amountOrDays = in.nextDouble();
                    account.deposit(amountOrDays);
                    break;
                case 1:
                    amountOrDays = in.nextDouble();
                    account.withdraw(amountOrDays);
                    break;
                case 2:
                    amountOrDays = in.nextDouble();
                    account.addDailyInterest((int) amountOrDays);
                    break;
                case 3:
                    System.out.printf("%.2f%n", account.getBalance());
                    break;
            }
        }

        in.close();
    }
}
