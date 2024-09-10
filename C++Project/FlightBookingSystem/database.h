#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

bool connectDatabase(const QString &databaseName) {
  QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL");
  database.setHostName("localhost");
  database.setPort(5432);
  database.setUserName("postgres");
  database.setPassword("123456");
  database.setDatabaseName(databaseName);

  if (!database.open()) {
    qDebug() << "Can't connect database!";
    return false;
  }

  return true;
}

#endif  // DATABASE_H
