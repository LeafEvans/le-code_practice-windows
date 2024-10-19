#include "logindialog.h"

#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
  ui->setupUi(this);
}

LoginDialog::~LoginDialog() { delete ui; }

void LoginDialog::getAllUsers() {
  QFile file("../data/user.txt");
  file.open(QFile::ReadOnly | QFile::Text);
  QByteArray usersByteData = file.readAll();
  QString usersStrData = QString(usersByteData);
  QStringList usersList = usersStrData.split("\n");

  for (int i = 0; i < usersList.size(); ++i) {
    QStringList temp = usersList[i].split(" ");
    if (temp.size() > 1) {
      this->users.append(new User(temp[0], temp[1]));
    }
  }

  file.close();
}

void LoginDialog::on_loginPushButton_clicked() {
  QString userName = ui->userLineEdit->text();
  QString password = ui->passwordLineEdit->text();

  this->getAllUsers();

  int flag = 0;

  for (int i = 0; i < users.size(); ++i) {
    if (!QString::compare(userName, users.at(i)->userName) &&
        !QString::compare(password, users.at(i)->password)) {
    }
  }
}
