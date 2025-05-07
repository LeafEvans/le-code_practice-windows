#include "logindialog.h"

#include "adminwindow.h"
#include "ui_logindialog.h"
#include "userwindow.h"

extern QString curUserTelNum;

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog) {
  ui->setupUi(this);
  setWindowTitle(tr("民航订票系统"));
  setWindowIcon(QIcon(":/image/airliner.svg"));
  ui->signInRadioButton->setChecked(true);
  ui->nameLabel->setVisible(false);
  ui->nameLineEdit->setVisible(false);
  ui->IDCardLabel->setVisible(false);
  ui->IDCardLineEdit->setVisible(false);
}

LoginDialog::~LoginDialog() { delete ui; }

/*
 * 设置窗口图片
 * */
void LoginDialog::paintEvent(QPaintEvent *event) {
  QPainter loginDialogPainter(this);
  loginDialogPainter.setOpacity(0.4);
  loginDialogPainter.drawPixmap(0, 0, this->width(), this->height(),
                                QPixmap(":/image/login_background"));
}

/*
 * 清空文本输入框
 * */
void LoginDialog::clearAll() {
  ui->nameLineEdit->clear();
  ui->IDCardLineEdit->clear();
  ui->telLineEdit->clear();
  ui->passwordLineEdit->clear();
}

/*
 * 转换管理员登录模式
 * */
void LoginDialog::on_adminPushButton_clicked() {
  clearAll();
  if (!isAdminMode) {
    isAdminMode = true;
    ui->signInRadioButton->setVisible(false);
    ui->signUpRadioButton->setVisible(false);
    ui->nameLabel->setVisible(false);
    ui->nameLineEdit->setVisible(false);
    ui->IDCardLabel->setVisible(false);
    ui->IDCardLineEdit->setVisible(false);
    ui->telLabel->setText(tr("管理员账号"));
    ui->passwordLabel->setText(tr("管理员密码"));
    ui->adminPushButton->setText("用户登录");
  } else {
    isAdminMode = false;
    ui->signInRadioButton->setVisible(true);
    ui->signUpRadioButton->setVisible(true);
    ui->telLabel->setText(tr("手机号码"));
    ui->passwordLabel->setText(tr("密码"));
    ui->adminPushButton->setText("管理员登录");
  }
}

/*
 * 转换注册模式
 * */
void LoginDialog::on_signInRadioButton_clicked() {
  clearAll();
  ui->adminPushButton->setVisible(true);
  ui->showPasswordPushButton->setText(tr("显示密码"));
  isShowPassword = false;
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  if (!isSignInMode) {
    isSignInMode = true;
    ui->nameLabel->setVisible(false);
    ui->nameLineEdit->setVisible(false);
    ui->IDCardLabel->setVisible(false);
    ui->IDCardLineEdit->setVisible(false);
    ui->loginPushButton->setText(tr("登录"));
  }
}

/*
 * 转换登录模式
 * */
void LoginDialog::on_signUpRadioButton_clicked() {
  clearAll();
  ui->adminPushButton->setVisible(false);
  ui->showPasswordPushButton->setText(tr("显示密码"));
  isShowPassword = false;
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  if (isSignInMode) {
    isSignInMode = false;
    ui->nameLabel->setVisible(true);
    ui->nameLineEdit->setVisible(true);
    ui->IDCardLabel->setVisible(true);
    ui->IDCardLineEdit->setVisible(true);
    ui->loginPushButton->setText(tr("注册"));
  }
}

void LoginDialog::on_showPasswordPushButton_clicked() {
  if (!isShowPassword) {
    isShowPassword = true;
    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    ui->showPasswordPushButton->setText(tr("隐藏密码"));
  } else {
    isShowPassword = false;
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->showPasswordPushButton->setText(tr("显示密码"));
  }
}

void LoginDialog::on_loginPushButton_clicked() {
  if (ui->adminPushButton->text() == "用户登录") {
    adminSignIn();
  } else if (ui->adminPushButton->text() == "管理员登录") {
    if (isSignInMode) {
      userSignIn();
    } else {
      userSignUp();
    }
  }
}

void LoginDialog::adminSignIn() {
  if (ui->telLineEdit->text().isEmpty() ||
      ui->passwordLineEdit->text().isEmpty()) {
    infoWindow(tr("请输入管理员账号及密码!"));
    clearAll();
    ui->telLineEdit->setFocus();
  } else {
    QString account = ui->telLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    QSqlTableModel tableModel;
    tableModel.setTable("admin_info");

    tableModel.setFilter(
        tr("admin_id = '%1' AND admin_pwd = '%2'").arg(account, password));
    tableModel.select();

    if (tableModel.rowCount() == 1) {
      this->close();
      AdminWindow *adminWindow = new AdminWindow;
      adminWindow->show();
    } else {
      infoWindow(tr("账户或密码错误, 请重新输入!"));
      clearAll();
      ui->telLineEdit->setFocus();
    }
  }
}

void LoginDialog::userSignIn() {
  if (ui->telLineEdit->text().isEmpty() ||
      ui->passwordLineEdit->text().isEmpty()) {
    infoWindow("请输入手机号码及密码!");
    clearAll();
    ui->telLineEdit->setFocus();
  } else {
    QString telNum = ui->telLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    QSqlTableModel tableModel;
    tableModel.setTable("user_info");
    tableModel.setFilter(
        tr("u_tel = '%1' AND u_pwd = '%2'").arg(telNum, password));
    tableModel.select();

    if (tableModel.rowCount() == 1) {
      curUserTelNum = telNum;
      this->close();
      infoWindow("登录成功!");
      UserWindow *userWindow = new UserWindow;
      userWindow->show();
    } else {
      infoWindow("手机号码或密码错误, 请重新输入!");
      clearAll();
      ui->telLineEdit->setFocus();
    }
  }
}

void LoginDialog::userSignUp() {
  QString name = ui->nameLineEdit->text();
  QString IDCard = ui->IDCardLineEdit->text();
  QString tel = ui->telLineEdit->text();
  QString password = ui->passwordLineEdit->text();

  QString signUpInfo =
      QString(
          "INSERT INTO user_info (u_name, u_IDCard, u_tel, u_pwd)"
          "VALUES ('%1', '%2', '%3', '%4');")
          .arg(name, IDCard, tel, password);

  if (name.isEmpty() || IDCard.isEmpty() || tel.isEmpty() ||
      password.isEmpty()) {
    infoWindow(tr("请输入完整信息!"));
    ui->IDCardLineEdit->setFocus();
  } else {
    QSqlTableModel tableModel;
    tableModel.setTable("user_info");
    tableModel.setFilter(
        tr("u_IDCard = '%1' AND u_tel = '%2'").arg(IDCard, tel));
    tableModel.select();

    if (tableModel.rowCount()) {
      infoWindow(tr("该用户已注册，请检查输入信息!"));
      ui->IDCardLineEdit->setFocus();
    } else {
      QSqlQuery query;

      if (query.exec(signUpInfo)) {
        infoWindow(tr("注册成功!"));
        ui->signInRadioButton->setChecked(true);
        on_signInRadioButton_clicked();  // 转换登录模式
      } else {
        infoWindow("注册失败, 请检查注册信息!");
      }
    }
  }
}

/*
 * 提示窗口函数
 * */
void LoginDialog::infoWindow(const QString &info) {
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Information);
  msgBox.setWindowIcon(QIcon(":/image/info.svg"));
  msgBox.setWindowTitle(tr("提示"));
  msgBox.setText(info);
  QFont font;
  font.setFamily("Alibaba PuHuiTi 3.0");
  font.setPointSize(12);
  msgBox.setFont(font);
  msgBox.exec();
}
