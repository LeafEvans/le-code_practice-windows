#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 连接 PostgreSQL 数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("test_database");
    db.setUserName("postgres");
    db.setPassword("123456");

    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              db.lastError().text());
        return -1;
    }

    MainWindow w;

    w.statusBar()->showMessage("Successfully connected to the database!");

    QSqlQuery insertQuery;
    if (!insertQuery.exec("INSERT INTO test_table (test_data) VALUES (42)")) {
        QMessageBox::critical(nullptr, QObject::tr("Insert Error"),
                              insertQuery.lastError().text());
    } else {
        w.statusBar()->showMessage("Data inserted successfully!");
    }

    QSqlQuery query;
    if (query.exec("SELECT * FROM test_table")) {
        while (query.next()) {
            int testData = query.value(0).toInt();
            w.statusBar()->showMessage("Test data: " + QString::number(testData));
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Query Error"),
                              query.lastError().text());
    }

    w.show();
    return app.exec();
}
