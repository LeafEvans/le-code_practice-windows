#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QHeaderView>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class UserWindow;
}
QT_END_NAMESPACE

class UserWindow : public QMainWindow {
  Q_OBJECT

 public:
  UserWindow(QWidget *parent = nullptr);
  ~UserWindow();

  void paintEvent(QPaintEvent *event) override;

 private:
  Ui::UserWindow *ui;

 private slots:

  void on_persCenterPushButton_clicked();

  void on_orderCenterPushButton_clicked();

  void on_flightQueryPushButton_clicked();

  void on_exitPushButton_clicked();

  void on_oneWayRadioButton_clicked();

  void on_twoWayRadioButton_clicked();

  void on_flightNumRadioButton_clicked();

  void on_flightDateRadioButton_clicked();

  void on_flightModePushButton_clicked();

  void on_bookingPushButton_clicked();

  void on_chDepCityComboBox_textActivated(const QString &arg1);

  void on_chArrCityComboBox_textActivated(const QString &arg1);

  void on_orderPaymentPushButton_clicked();

  void on_cancelButtonPushButton_clicked();

  void on_deleteOrderPushButton_clicked();

 private:
  void initUserWindow();

  void initUserInfo();

  void clearFlightQueryTable();

  void clearOrderCenterTable();

  void clearPersCenterTable();

  void flightCityQuery();

  void flightNumQuery();

  void flightDateQuery();

  void infoWindow(const QString &info);

  int questionWindow(const QString &question);

  void persCenterShow();

  void orderCenterShow();

 private:
  QString userTel;
  QString userName;

  QString persTicketNum;
  QString persUserName;
  QString persFlightNum;
  QString persDepCity;
  QString persArrCity;
  QString persDepDate;
  QString persDepTime;
  QString persFlightPrice;

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

  QString eleTicketNum;
  QString eleOrderNum;
  QString eleTicketUserName;
  QString eleFlightNum;
  QString eleFlightDate;
  QString eleFlightTime;
  QString eleFlightDepCity;
  QString eleFlightArrCity;
  QString eleFlightPrice;
};
#endif  // USERWINDOW_H
