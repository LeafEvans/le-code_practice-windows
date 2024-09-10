#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "user.h"

#include <QDialog>
#include <QFile>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    void getAllUsers();

    QList<User *> users;

private slots:
    void on_loginPushButton_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
