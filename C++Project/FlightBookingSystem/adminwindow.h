#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit AdminWindow(QWidget *parent = nullptr);
  ~AdminWindow();

  void paintEvent(QPaintEvent *event) override;

 private slots:
  void on_exitPushButton_clicked();

  void on_orderInfoPushButton_clicked();

  void on_userInfoPushButton_clicked();

  void on_flightInfoPushButton_clicked();

  void on_flightNumRadioButton_clicked();

  void on_flightDateRadioButton_clicked();

  void on_flightQueryPushButton_clicked();

  void on_flightModifyPushButton_clicked();

  void on_flightDeletePushButton_clicked();

  void on_orderModifyPushButton_clicked();

  void on_orderQueryPushButton_clicked();

  void on_orderDeletePushButton_clicked();

  void on_userQueryPushButton_clicked();

  void on_userModifyPushButton_clicked();

  void on_userDeletePushButton_clicked();

 private:
  Ui::AdminWindow *ui;

  QString flightNum;
  QString flightPrice;
  QString flightDepDate;
  QString flightArrDate;
  QString flightDepTime;
  QString flightDis;
  QString flightType;
  QString flightCroCity;
  QString flightDepCity;
  QString flightArrCity;

  QString orderNum;
  QString orderFlightNum;
  QString orderUserTel;
  QString orderUserName;
  QString orderPayState;
  QString orderFlightDate;
  QString orderFlightTime;
  QString orderFlightDepCity;
  QString orderFlightArrCity;
  QString orderFlightPrice;
  QString orderTime;
  QString orderPayTime;

  QString userName;
  QString userIDCard;
  QString userTel;
  QString userPassword;

 private:
  void initAdminWindow();

  void clearOrderInfoTable();

  void clearUserInfoTable();

  void clearFlightInfoTable();

  void flightNumQuery();

  void flightDateQuery();

  void infoWindow(const QString &info);

  int questionWindow(const QString &question);
};

#endif  // ADMINWINDOW_H
