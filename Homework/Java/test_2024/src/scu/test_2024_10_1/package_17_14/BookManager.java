package scu.test_2024_10_1.package_17_14;

public class BookManager {
    Book[] books = new Book[50];

    public void initBooks() {
        Book book = new Book();
        book.bookName = "阿泰勒的角落";
        book.bookAuthor = "李娟";
        book.price = 45;
        books[0] = book;

        Book book2 = new Book();
        book2.bookName = "平凡的世界";
        book2.bookAuthor = "路遥";
        book2.price = 55;
        books[1] = book2;
    }

    public void bookList() {
        System.out.println("这里是图书列表");
        System.out.println("书名\t\t\t作者\t\t价格");
        for (int i = 0; i < books.length; ++i) {
            if (books[i] != null) {
                System.out.println(books[i].bookName + "\t\t"
                        + books[i].bookAuthor + "\t\t"
                        + books[i].price);
            }
        }
    }

    public void addBook(Book book) {
        for (int i = 0; i < books.length; ++i) {
            if (books[i] == null) {
                books[i] = book;
                break;
            }
        }
    }
}
