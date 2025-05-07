#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QFile>
#include <QList>
#include <QMessageBox>

#include "mainwindow.h"
#include "user.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
  Q_OBJECT

 public:
  explicit LoginDialog(QWidget *parent = nullptr);
  ~LoginDialog();

  QList<User *> users;

  void getAllUsers();

  User *curUser;

  MainWindow *mainWindow;

 private slots:
  void on_loginButton_clicked();

  void on_logoutButton_clicked();

 signals:
  void sendUser(User *user);

 private:
  Ui::LoginDialog *ui;
};

#endif  // LOGINDIALOG_H
