package scu.test_2024_10_1.package_17_14;

import java.util.Scanner;

public class T1 {

    public static void menu() {
        System.out.println("欢迎来到图书管理系统");
        System.out.println("1、图书列表");
        System.out.println("2、添加图书");
        System.out.println("0、退出系统");
        System.out.println("请输入对应操作，输入数字即可");
    }

    public static void main(String[] args) {
        BookManager manager = new BookManager();
        manager.initBooks();
        menu();
        Scanner input = new Scanner(System.in);
        int num;
        do {
            num = input.nextInt();
            switch (num) {
                case 1:
                    manager.bookList();
                    menu();
                    break;

                case 2:
                    System.out.println("这里是添加图书界面");
                    Book book = new Book();
                    System.out.println("请输入图书名称");
                    book.bookName = input.next();
                    System.out.println("请输入图书作者");
                    book.bookAuthor = input.next();
                    System.out.println("请输入图书价格");
                    book.price = input.nextInt();
                    manager.addBook(book);
                    menu();
                    break;
                case 0:
                    break;
                default:
                    break;
            }
        } while (num != 0);
        System.out.println("感谢您使用该系统");
        input.close();
    }
}
