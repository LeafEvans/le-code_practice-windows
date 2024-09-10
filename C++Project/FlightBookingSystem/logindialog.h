#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QByteArray>
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QPaintEvent>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
  Q_OBJECT

 public:
  explicit LoginDialog(QWidget *parent = nullptr);
  ~LoginDialog();

  void paintEvent(QPaintEvent *event) override;

 private slots:
  void on_adminPushButton_clicked();

  void on_signInRadioButton_clicked();

  void on_signUpRadioButton_clicked();

  void on_showPasswordPushButton_clicked();

  void on_loginPushButton_clicked();

 private:
  Ui::LoginDialog *ui;

  bool isShowPassword = false;  // 默认不显示密码
  bool isSignInMode = true;     // 默认登录模式
  bool isAdminMode = false;     // 默认用户登录模式

 private:
  void clearAll();

  void userSignIn();

  void userSignUp();

  void adminSignIn();

  void infoWindow(const QString &);
};

#endif  // LOGINDIALOG_H
