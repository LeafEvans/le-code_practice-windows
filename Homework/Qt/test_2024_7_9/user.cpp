#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{}

User::User(QString userName, QString password) {
    this->userName = userName;
    this->password = password;
}
