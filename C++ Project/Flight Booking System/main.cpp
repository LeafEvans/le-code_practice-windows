#include <QApplication>

#include "database.h"
#include "logindialog.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFile styleFile(":/qss/MacOS.qss");
  if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream ts(&styleFile);
    qApp->setStyleSheet(ts.readAll());
    styleFile.close();
  } else {
    qDebug() << "Failed to load style sheet.";
  }

  if (connectDatabase("flight_database")) {
    qDebug() << "Connect database success!";
  } else {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("连接数据库错误");
    msgBox.setText("<font color='red'>无法连接到数据库</font>");
    msgBox.setWindowIcon(QIcon(":/image/critical.svg"));
    return msgBox.exec();
  }

  LoginDialog w;
  w.show();

  return a.exec();
}
