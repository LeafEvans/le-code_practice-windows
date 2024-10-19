#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject {
  Q_OBJECT
 public:
  explicit User(QObject *parent = nullptr);
  User(QString userName, QString password);
  QString userName;
  QString password;

 signals:
};

#endif  // USER_H
