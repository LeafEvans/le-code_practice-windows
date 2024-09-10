#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    mainWindow = new MainWindow;
    setWindowTitle("图书管理系统");
    setWindowIcon(QIcon(":/icon/logo.png"));
    connect(this, &LoginDialog::sendUser,
            mainWindow, &MainWindow::recUser);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::getAllUsers() {
    QFile file("C:\\Code\\CodePractice\\Homework\\Qt\\test_2024_7_9\\data\\users.txt");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QByteArray byteData = file.readAll();
        QString strData(byteData);
        QStringList listData = strData.split("\n");

        for (int i = 0; i < listData.size(); ++i) {
            QStringList user = listData[i].split(" ");
            users.append(new User(user[0], user[1]));
        }

        file.close();
    } else {
        QMessageBox::warning(this, "Error", "系统暂未开放");
    }
}

void LoginDialog::on_loginButton_clicked() {
    ui->warningLabel->setText("");
    this->getAllUsers();
    auto userName = ui->userNameLabel->text();
    auto password = ui->passwordLabel->text();

    bool flag = false;

    for (int i = 0; i < users.size(); ++i) {
        if (!users[i]->userName.compare(userName)
            && !users[i]->password.compare(password)) {
            flag = true;
            curUser = users[i];
            break;
        }
    }

    if (flag) {
        emit sendUser(curUser);
        this->hide();
        mainWindow->show();
    } else {
        ui->warningLabel->setText("用户名或密码错误");
        ui->warningLabel->setStyleSheet("color:red");
    }
}


void LoginDialog::on_logoutButton_clicked() {
    QApplication::exit();
}

