#include "adminwindow.h"

#include "logindialog.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AdminWindow) {
  ui->setupUi(this);
  initAdminWindow();
}

void AdminWindow::paintEvent(QPaintEvent *event) {
  QPainter adminWindowPainter(this);
  adminWindowPainter.setOpacity(0.5);
  adminWindowPainter.drawPixmap(0, 0, this->width(), this->height(),
                                QPixmap(":/image/admin_background.jpg"));
}

AdminWindow::~AdminWindow() { delete ui; }

void AdminWindow::initAdminWindow() {
  setWindowTitle("系统管理员");
  setWindowIcon(QIcon(":/image/admin.svg"));
  ui->flightDateRadioButton->setCheckable(true);
  ui->flightDateEdit->setCalendarPopup(true);
  ui->flightDateEdit->setDate(QDate::currentDate());
  ui->flightInfoTableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->orderInfoTableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->userInfoTableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->flightInfoTableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->orderInfoTableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->userInfoTableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->flightNumLineEdit->setReadOnly(true);
}

void AdminWindow::on_exitPushButton_clicked() {
  if (questionWindow("确定退出管理员系统吗?") == QMessageBox::Yes) {
    this->close();
    LoginDialog *loginDialog = new LoginDialog;
    loginDialog->show();
  }
}

void AdminWindow::on_orderInfoPushButton_clicked() {
  ui->stackedWidget->setCurrentWidget(ui->orderInfoPage);
}

void AdminWindow::on_userInfoPushButton_clicked() {
  ui->stackedWidget->setCurrentWidget(ui->userInfoPage);
}

void AdminWindow::on_flightInfoPushButton_clicked() {
  ui->stackedWidget->setCurrentWidget(ui->flightInfoPage);
}

void AdminWindow::clearOrderInfoTable() {
  ui->orderInfoTableWidget->clearContents();
  ui->orderInfoTableWidget->setRowCount(0);
}

void AdminWindow::clearUserInfoTable() {
  ui->userInfoTableWidget->clearContents();
  ui->userInfoTableWidget->setRowCount(0);
}

void AdminWindow::clearFlightInfoTable() {
  ui->flightInfoTableWidget->clearContents();
  ui->flightInfoTableWidget->setRowCount(0);
}

void AdminWindow::on_flightNumRadioButton_clicked() {
  ui->flightQueryPushButton->setText("航班号查询");
  ui->flightNumLineEdit->setReadOnly(false);
  ui->flightDateEdit->setReadOnly(true);
  ui->flightNumLineEdit->clear();
  clearFlightInfoTable();
}

void AdminWindow::on_flightDateRadioButton_clicked() {
  ui->flightQueryPushButton->setText("航班日期查询");
  ui->flightNumLineEdit->setReadOnly(true);
  ui->flightDateEdit->setReadOnly(false);
  ui->flightNumLineEdit->clear();
  clearFlightInfoTable();
}

void AdminWindow::on_flightQueryPushButton_clicked() {
  if (ui->flightQueryPushButton->text() == "航班号查询") {
    flightNumQuery();
  } else {
    flightDateQuery();
  }
}

void AdminWindow::flightNumQuery() {
    clearFlightInfoTable();
    flightNum = ui->flightNumLineEdit->text();

    if (flightNum.isEmpty()) {
        infoWindow("请输入航班号!");
        return;
    }

    QSqlTableModel *flightNumModel = new QSqlTableModel(this);
    flightNumModel->setTable("flight_info");
    flightNumModel->setFilter(tr("f_num = '%1'").arg(flightNum));
    flightNumModel->select();

    if (flightNumModel->rowCount() != 1) {
        infoWindow("未查询到该航班相关信息!");
        ui->flightNumLineEdit->clear();
        ui->flightNumLineEdit->setFocus();
        clearFlightInfoTable();
        delete flightNumModel;
        return;
    }

    flightNum = flightNumModel->data(flightNumModel->index(0, 0)).toString();
    flightPrice = flightNumModel->data(flightNumModel->index(0, 1)).toString();
    flightDepDate = flightNumModel->data(flightNumModel->index(0, 2)).toString();
    flightArrDate = flightNumModel->data(flightNumModel->index(0, 3)).toString();
    flightDepTime = flightNumModel->data(flightNumModel->index(0, 4)).toString();
    flightDis = flightNumModel->data(flightNumModel->index(0, 5)).toString();
    flightType = flightNumModel->data(flightNumModel->index(0, 6)).toString();
    flightCroCity = flightNumModel->data(flightNumModel->index(0, 7)).toString();
    flightDepCity = flightNumModel->data(flightNumModel->index(0, 8)).toString();
    flightArrCity = flightNumModel->data(flightNumModel->index(0, 9)).toString();

    int rowCount = ui->flightInfoTableWidget->rowCount();
    ui->flightInfoTableWidget->insertRow(rowCount);

    auto check = new QTableWidgetItem();
    check->setCheckState(Qt::Unchecked);

    ui->flightInfoTableWidget->setItem(rowCount, 0, check);
    ui->flightInfoTableWidget->setItem(rowCount, 1, new QTableWidgetItem(flightNum));
    ui->flightInfoTableWidget->setItem(rowCount, 2, new QTableWidgetItem(flightPrice));
    ui->flightInfoTableWidget->setItem(rowCount, 3, new QTableWidgetItem(flightDepDate));
    ui->flightInfoTableWidget->setItem(rowCount, 4, new QTableWidgetItem(flightArrDate));
    ui->flightInfoTableWidget->setItem(rowCount, 5, new QTableWidgetItem(flightDepTime));
    ui->flightInfoTableWidget->setItem(rowCount, 6, new QTableWidgetItem(flightDis));
    ui->flightInfoTableWidget->setItem(rowCount, 7, new QTableWidgetItem(flightType));
    ui->flightInfoTableWidget->setItem(rowCount, 8, new QTableWidgetItem(flightDepCity));
    ui->flightInfoTableWidget->setItem(rowCount, 9, new QTableWidgetItem(flightArrCity));
    ui->flightInfoTableWidget->setItem(rowCount, 10, new QTableWidgetItem(flightCroCity));

    ui->flightInfoTableWidget->item(rowCount, 1)->setFlags(
        ui->flightInfoTableWidget->item(rowCount, 1)->flags() & (~Qt::ItemIsEditable));

    delete flightNumModel;
}


void AdminWindow::flightDateQuery() {
    clearFlightInfoTable();

    flightDepDate = ui->flightDateEdit->date().toString("yyyy-MM-dd");

    QSqlTableModel *flightDateModel = new QSqlTableModel(this);
    flightDateModel->setTable("flight_info");
    flightDateModel->setFilter(tr("f_dep_date = '%1'").arg(flightDepDate));
    flightDateModel->select();

    if (!(flightDateModel->rowCount() >= 1)) {
        infoWindow("未查询到该日期相关航班信息!");
        clearFlightInfoTable();
        delete flightDateModel;
        return;
    }

    for (int i = 0; i < flightDateModel->rowCount(); ++i) {
        flightNum = flightDateModel->data(flightDateModel->index(i, 0)).toString();
        flightPrice = flightDateModel->data(flightDateModel->index(i, 1)).toString();
        flightDepDate = flightDateModel->data(flightDateModel->index(i, 2)).toString();
        flightArrDate = flightDateModel->data(flightDateModel->index(i, 3)).toString();
        flightDepTime = flightDateModel->data(flightDateModel->index(i, 4)).toString();
        flightDis = flightDateModel->data(flightDateModel->index(i, 5)).toString();
        flightType = flightDateModel->data(flightDateModel->index(i, 6)).toString();
        flightCroCity = flightDateModel->data(flightDateModel->index(i, 7)).toString();
        flightDepCity = flightDateModel->data(flightDateModel->index(i, 8)).toString();
        flightArrCity = flightDateModel->data(flightDateModel->index(i, 9)).toString();

        int rowCount = ui->flightInfoTableWidget->rowCount();
        ui->flightInfoTableWidget->insertRow(rowCount);

        auto check = new QTableWidgetItem;
        check->setCheckState(Qt::Unchecked);

        ui->flightInfoTableWidget->setItem(rowCount, 0, check);
        ui->flightInfoTableWidget->setItem(rowCount, 1, new QTableWidgetItem(flightNum));
        ui->flightInfoTableWidget->setItem(rowCount, 2, new QTableWidgetItem(flightPrice));
        ui->flightInfoTableWidget->setItem(rowCount, 3, new QTableWidgetItem(flightDepDate));
        ui->flightInfoTableWidget->setItem(rowCount, 4, new QTableWidgetItem(flightArrDate));
        ui->flightInfoTableWidget->setItem(rowCount, 5, new QTableWidgetItem(flightDepTime));
        ui->flightInfoTableWidget->setItem(rowCount, 6, new QTableWidgetItem(flightDis));
        ui->flightInfoTableWidget->setItem(rowCount, 7, new QTableWidgetItem(flightType));
        ui->flightInfoTableWidget->setItem(rowCount, 8, new QTableWidgetItem(flightDepCity));
        ui->flightInfoTableWidget->setItem(rowCount, 9, new QTableWidgetItem(flightArrCity));
        ui->flightInfoTableWidget->setItem(rowCount, 10, new QTableWidgetItem(flightCroCity));
        ui->flightInfoTableWidget->item(i, 1)->setFlags(
            ui->flightInfoTableWidget->item(i, 1)->flags() & (~Qt::ItemIsEditable));
    }

    delete flightDateModel;
}


void AdminWindow::on_flightModifyPushButton_clicked() {
    QList<int> infoList;

    for (int i = 0; i < ui->flightInfoTableWidget->rowCount(); ++i) {
        if (ui->flightInfoTableWidget->item(i, 0)->checkState()) {
            infoList << i;
        }
    }

    if (infoList.isEmpty()) {
        infoWindow("请选择需要修改的航班!");
        return;
    }

    if (questionWindow("确认修改该航班信息吗?") == QMessageBox::No) {
        infoWindow("您已取消航班信息修改!");
        return;
    }

    for (int i = 0; i < infoList.size(); ++i) {
        QString flightNum = ui->flightInfoTableWidget->item(infoList.at(i), 1)->text();

        QSqlTableModel *flightInfoModel = new QSqlTableModel(this);
        flightInfoModel->setTable("flight_info");
        flightInfoModel->setFilter(tr("f_num = '%1'").arg(flightNum));
        flightInfoModel->select();

        if (flightInfoModel->rowCount() == 1) {
            QString flightPrice = ui->flightInfoTableWidget->item(infoList.at(i), 2)->text();
            QString flightDepDate = ui->flightInfoTableWidget->item(infoList.at(i), 3)->text();
            QString flightArrDate = ui->flightInfoTableWidget->item(infoList.at(i), 4)->text();
            QString flightDepTime = ui->flightInfoTableWidget->item(infoList.at(i), 5)->text();
            QString flightDis = ui->flightInfoTableWidget->item(infoList.at(i), 6)->text();
            QString flightType = ui->flightInfoTableWidget->item(infoList.at(i), 7)->text();
            QString flightCroCity = ui->flightInfoTableWidget->item(infoList.at(i), 10)->text();
            QString flightDepCity = ui->flightInfoTableWidget->item(infoList.at(i), 8)->text();
            QString flightArrCity = ui->flightInfoTableWidget->item(infoList.at(i), 9)->text();

            QString modifyInfo =
                tr("UPDATE flight_info SET f_price = '%1', f_dep_date = '%2',"
                   "f_arr_date = '%3', f_dep_time = '%4',"
                   "f_dis = '%5', f_type = '%6',"
                   "f_cro_city = '%7', f_dep_city = '%8',"
                   "f_arr_city = '%9' WHERE f_num = '%10'")
                    .arg(flightPrice, flightDepDate, flightArrDate, flightDepTime,
                         flightDis, flightType, flightCroCity, flightDepCity,
                         flightArrCity, flightNum);

            QSqlQuery *modifyQuery = new QSqlQuery;
            if (modifyQuery->exec(modifyInfo)) {
                infoWindow(tr("修改航班 %1 成功!").arg(flightNum));
                ui->flightInfoTableWidget->item(infoList.at(i), 0)->setCheckState(Qt::Unchecked);
            } else {
                infoWindow(tr("修改航班 %1 失败!").arg(flightNum));
            }

            delete modifyQuery;
        }

        delete flightInfoModel;
    }

    on_flightQueryPushButton_clicked();
}


void AdminWindow::on_flightDeletePushButton_clicked() {
    QList<int> infoList;

    for (int i = 0; i < ui->flightInfoTableWidget->rowCount(); ++i) {
        if (ui->flightInfoTableWidget->item(i, 0)->checkState()) {
            infoList << i;
        }
    }

    if (infoList.isEmpty()) {
        infoWindow("请选择需要删除的航班!");
        return;
    }

    if (questionWindow("确认删除该航班信息吗?") == QMessageBox::No) {
        infoWindow("您已取消删除航班信息!");
        return;
    }

    for (int i = 0; i < infoList.size(); ++i) {
        QString flightNum = ui->flightInfoTableWidget->item(infoList.at(i), 1)->text();

        QSqlTableModel *flightInfoModel = new QSqlTableModel(this);
        flightInfoModel->setTable("flight_info");
        flightInfoModel->setFilter(tr("f_num = '%1'").arg(flightNum));
        flightInfoModel->select();

        if (flightInfoModel->rowCount() == 1) {
            QString deleteInfo = tr("DELETE FROM flight_info WHERE f_num = '%1'").arg(flightNum);

            QSqlQuery *deleteQuery = new QSqlQuery;
            if (deleteQuery->exec(deleteInfo)) {
                infoWindow(tr("删除航班 %1 成功!").arg(flightNum));
                ui->flightInfoTableWidget->item(infoList.at(i), 0)->setCheckState(Qt::Unchecked);
            } else {
                infoWindow(tr("删除航班 %1 失败!").arg(flightNum));
            }

            delete deleteQuery;
        }

        delete flightInfoModel;
    }

    on_flightQueryPushButton_clicked();
}


void AdminWindow::infoWindow(const QString &info) {
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

int AdminWindow::questionWindow(const QString &question) {
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Question);
  msgBox.setWindowIcon(QIcon(":/image/question.svg"));
  msgBox.setWindowTitle(tr("提示"));
  msgBox.setText(question);
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.setDefaultButton(QMessageBox::No);
  QFont font;
  font.setFamily("Alibaba PuHuiTi 3.0");
  font.setPointSize(12);
  msgBox.setFont(font);
  return msgBox.exec();
}

void AdminWindow::on_orderQueryPushButton_clicked() {
    clearOrderInfoTable();

    ui->orderInfoTableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);

    orderNum = ui->orderNumLineEdit->text();

    QSqlTableModel *orderInfoModel = new QSqlTableModel(this);
    orderInfoModel->setTable("order_info");
    orderInfoModel->setFilter(tr("order_num = '%1'").arg(orderNum));
    orderInfoModel->select();

    if (orderInfoModel->rowCount() != 1) {
        infoWindow("未查询到该订单!");
        delete orderInfoModel;
        return;
    }

    orderFlightNum = orderInfoModel->data(orderInfoModel->index(0, 1)).toString();
    orderUserTel = orderInfoModel->data(orderInfoModel->index(0, 2)).toString();
    orderUserName = orderInfoModel->data(orderInfoModel->index(0, 3)).toString();
    orderPayState = orderInfoModel->data(orderInfoModel->index(0, 4)).toString();
    orderFlightDate = orderInfoModel->data(orderInfoModel->index(0, 5)).toString();
    orderFlightTime = orderInfoModel->data(orderInfoModel->index(0, 6)).toString();
    orderFlightDepCity =
        orderInfoModel->data(orderInfoModel->index(0, 7)).toString();
    orderFlightArrCity =
        orderInfoModel->data(orderInfoModel->index(0, 8)).toString();
    orderFlightPrice = orderInfoModel->data(orderInfoModel->index(0, 9)).toString();
    orderTime = orderInfoModel->data(orderInfoModel->index(0, 10)).toString();
    orderPayTime = orderInfoModel->data(orderInfoModel->index(0, 11)).toString();

    int rowCount = ui->orderInfoTableWidget->rowCount();
    ui->orderInfoTableWidget->insertRow(rowCount);

    auto *check = new QTableWidgetItem();
    check->setCheckState(Qt::Unchecked);
    ui->orderInfoTableWidget->setItem(rowCount, 0, check);

    QTableWidgetItem *itemOrderNum = new QTableWidgetItem(orderNum);
    QTableWidgetItem *itemFlightNum = new QTableWidgetItem(orderFlightNum);
    QTableWidgetItem *itemUserTel = new QTableWidgetItem(orderUserTel);
    QTableWidgetItem *itemUserName = new QTableWidgetItem(orderUserName);
    QTableWidgetItem *itemPayState = new QTableWidgetItem(orderPayState);
    QTableWidgetItem *itemFlightDate = new QTableWidgetItem(orderFlightDate);
    QTableWidgetItem *itemFlightTime = new QTableWidgetItem(orderFlightTime);
    QTableWidgetItem *itemFlightDepCity = new QTableWidgetItem(orderFlightDepCity);
    QTableWidgetItem *itemFlightArrCity = new QTableWidgetItem(orderFlightArrCity);
    QTableWidgetItem *itemFlightPrice = new QTableWidgetItem(orderFlightPrice);
    QTableWidgetItem *itemOrderTime = new QTableWidgetItem(orderTime);
    QTableWidgetItem *itemPayTime = new QTableWidgetItem(orderPayTime);

    ui->orderInfoTableWidget->setItem(rowCount, 1, itemOrderNum);
    ui->orderInfoTableWidget->setItem(rowCount, 2, itemFlightNum);
    ui->orderInfoTableWidget->setItem(rowCount, 3, itemUserTel);
    ui->orderInfoTableWidget->setItem(rowCount, 4, itemUserName);
    ui->orderInfoTableWidget->setItem(rowCount, 5, itemPayState);
    ui->orderInfoTableWidget->setItem(rowCount, 6, itemFlightDate);
    ui->orderInfoTableWidget->setItem(rowCount, 7, itemFlightTime);
    ui->orderInfoTableWidget->setItem(rowCount, 8, itemFlightDepCity);
    ui->orderInfoTableWidget->setItem(rowCount, 9, itemFlightArrCity);
    ui->orderInfoTableWidget->setItem(rowCount, 10, itemFlightPrice);
    ui->orderInfoTableWidget->setItem(rowCount, 11, itemOrderTime);
    ui->orderInfoTableWidget->setItem(rowCount, 12, itemPayTime);

    itemOrderNum->setFlags(itemOrderNum->flags() & (~Qt::ItemIsEditable));
    itemPayState->setFlags(itemPayState->flags() & (~Qt::ItemIsEditable));

    delete orderInfoModel;
}


void AdminWindow::on_orderModifyPushButton_clicked() {
    QList<int> infoList;

    for (int i = 0; i < ui->orderInfoTableWidget->rowCount(); ++i) {
        if (ui->orderInfoTableWidget->item(i, 0)->checkState()) {
            infoList << i;
        }
    }

    if (infoList.isEmpty()) {
        infoWindow("请选择需要修改的订单!");
        return;
    }

    if (questionWindow("确认修改该订单吗?") == QMessageBox::No) {
        infoWindow("您已取消订单修改!");
        return;
    }

    for (int i = 0; i < infoList.size(); ++i) {
        QString orderNum = ui->orderInfoTableWidget->item(infoList.at(i), 1)->text();

        QSqlTableModel *orderInfoModel = new QSqlTableModel(this);
        orderInfoModel->setTable("order_info");
        orderInfoModel->setFilter(tr("order_num = '%1'").arg(orderNum));
        orderInfoModel->select();

        if (orderInfoModel->rowCount() == 1) {
            orderFlightNum = ui->orderInfoTableWidget->item(infoList.at(i), 2)->text();
            orderUserTel = ui->orderInfoTableWidget->item(infoList.at(i), 3)->text();
            orderUserName = ui->orderInfoTableWidget->item(infoList.at(i), 4)->text();
            orderPayState = ui->orderInfoTableWidget->item(infoList.at(i), 5)->text();
            orderFlightDate = ui->orderInfoTableWidget->item(infoList.at(i), 6)->text();
            orderFlightTime = ui->orderInfoTableWidget->item(infoList.at(i), 7)->text();
            orderFlightDepCity = ui->orderInfoTableWidget->item(infoList.at(i), 8)->text();
            orderFlightArrCity = ui->orderInfoTableWidget->item(infoList.at(i), 9)->text();
            orderFlightPrice = ui->orderInfoTableWidget->item(infoList.at(i), 10)->text();
            orderTime = ui->orderInfoTableWidget->item(infoList.at(i), 11)->text();
            orderPayTime = ui->orderInfoTableWidget->item(infoList.at(i), 12)->text();

            QString modifyInfo =
                tr("UPDATE order_info SET order_flight_num = '%1',"
                   "order_u_tel = '%2', order_u_name = '%3',"
                   "order_pay_state = '%4', order_flight_date = '%5',"
                   "order_flight_time = '%6', order_flight_dep_city = '%7',"
                   "order_flight_arr_city = '%8', order_flight_price = '%9',"
                   "order_time = '%10', order_pay_time = '%11'"
                   "WHERE order_num = '%12'")
                    .arg(orderFlightNum, orderUserTel, orderUserName, orderPayState,
                         orderFlightDate, orderFlightTime, orderFlightDepCity,
                         orderFlightArrCity, orderFlightPrice, orderTime,
                         orderPayTime, orderNum);

            QSqlQuery modifyQuery;

            if (modifyQuery.exec(modifyInfo)) {
                infoWindow(tr("修改订单 %1 成功!").arg(orderNum));
                ui->orderInfoTableWidget->item(infoList.at(i), 0)
                    ->setCheckState(Qt::Unchecked);
            } else {
                infoWindow(tr("修改订单 %1 失败!").arg(orderNum));
            }
        }

        delete orderInfoModel;
    }

    on_orderQueryPushButton_clicked();
}


void AdminWindow::on_orderDeletePushButton_clicked() {
    QList<int> infoList;

    for (int i = 0; i < ui->orderInfoTableWidget->rowCount(); ++i) {
        if (ui->orderInfoTableWidget->item(i, 0)->checkState()) {
            infoList << i;
        }
    }

    if (infoList.isEmpty()) {
        infoWindow("请选择需要删除的订单!");
        return;
    }

    if (questionWindow("确认删除该订单吗?") == QMessageBox::No) {
        infoWindow("您已取消订单删除!");
        return;
    }

    for (int i = 0; i < infoList.size(); ++i) {
        orderNum = ui->orderInfoTableWidget->item(infoList.at(i), 1)->text();

        QSqlTableModel *orderInfoModel = new QSqlTableModel(this);
        orderInfoModel->setTable("order_info");
        orderInfoModel->setFilter(tr("order_num = '%1'").arg(orderNum));
        orderInfoModel->select();

        if (orderInfoModel->rowCount() == 1) {
            auto deleteInfo =
                tr("DELETE FROM order_info WHERE order_num = '%1'").arg(orderNum);

            QSqlQuery deleteQuery;

            if (deleteQuery.exec(deleteInfo)) {
                infoWindow(tr("删除订单 %1 成功!").arg(orderNum));
                clearOrderInfoTable();
                ui->orderNumLineEdit->clear();
                ui->orderNumLineEdit->setFocus();
            } else {
                infoWindow(tr("删除订单 %1 失败!").arg(orderNum));
            }
        }

        delete orderInfoModel;
    }
}


void AdminWindow::on_userQueryPushButton_clicked() {
    clearUserInfoTable();

    ui->userInfoTableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);

    userTel = ui->userTelLineEdit->text();

    QSqlTableModel *userInfoModel = new QSqlTableModel(this);
    userInfoModel->setTable("user_info");
    userInfoModel->setFilter(tr("u_tel = '%1'").arg(userTel));
    userInfoModel->select();

    if (userInfoModel->rowCount() == 0) {
        infoWindow("未查询到该用户信息!");
        delete userInfoModel;
        return;
    }

    userName = userInfoModel->data(userInfoModel->index(0, 0)).toString();
    userIDCard = userInfoModel->data(userInfoModel->index(0, 1)).toString();
    userPassword = userInfoModel->data(userInfoModel->index(0, 3)).toString();

    int rowCount = ui->userInfoTableWidget->rowCount();
    ui->userInfoTableWidget->insertRow(rowCount);

    auto check = new QTableWidgetItem();
    check->setCheckState(Qt::Unchecked);

    ui->userInfoTableWidget->setItem(rowCount, 0, check);
    ui->userInfoTableWidget->setItem(rowCount, 1, new QTableWidgetItem(userName));
    ui->userInfoTableWidget->setItem(rowCount, 2,
                                     new QTableWidgetItem(userIDCard));
    ui->userInfoTableWidget->setItem(rowCount, 3, new QTableWidgetItem(userTel));
    ui->userInfoTableWidget->setItem(rowCount, 4,
                                     new QTableWidgetItem(userPassword));


    ui->userInfoTableWidget->item(rowCount, 3)->setFlags(
        ui->userInfoTableWidget->item(rowCount, 3)->flags() & (~Qt::ItemIsEditable));

    delete userInfoModel;
}


void AdminWindow::on_userModifyPushButton_clicked() {
    QList<int> infoList;

    for (int i = 0; i < ui->userInfoTableWidget->rowCount(); ++i) {
        if (ui->userInfoTableWidget->item(i, 0)->checkState()) {
            infoList << i;
        }
    }

    if (infoList.isEmpty()) {
        infoWindow("请选择需要修改的用户!");
        return;
    }

    if (questionWindow("确定修改该用户吗?") == QMessageBox::No) {
        infoWindow("您已取消修改该用户!");
        return;
    }

    for (int i = 0; i < infoList.size(); ++i) {
        QSqlTableModel *userInfoModel = new QSqlTableModel(this);
        userInfoModel->setTable("user_info");
        userInfoModel->setFilter(tr("u_tel = '%1'")
                                     .arg(ui->userInfoTableWidget->item(infoList.at(i), 3)->text()));
        userInfoModel->select();

        if (userInfoModel->rowCount() == 1) {
            userName = ui->userInfoTableWidget->item(infoList.at(i), 1)->text();
            userIDCard = ui->userInfoTableWidget->item(infoList.at(i), 2)->text();
            userTel = ui->userInfoTableWidget->item(infoList.at(i), 3)->text();
            userPassword = ui->userInfoTableWidget->item(infoList.at(i), 4)->text();

            auto modifyInfo =
                tr("UPDATE user_info SET u_name = '%1', u_IDCard = '%2', u_pwd = '%3'"
                   "WHERE u_tel = '%4'")
                    .arg(userName, userIDCard, userPassword, userTel);

            QSqlQuery modifyQuery;
            if (modifyQuery.exec(modifyInfo)) {
                infoWindow(tr("修改用户%1成功!").arg(userName));
                ui->userInfoTableWidget->item(infoList.at(i), 0)->setCheckState(Qt::Unchecked);
            } else {
                infoWindow(tr("修改用户%1失败!").arg(userName));
            }
        }

        delete userInfoModel;
    }

    on_userQueryPushButton_clicked();
}



void AdminWindow::on_userDeletePushButton_clicked() {
    QList<int> infoList;

    for (int i = 0; i < ui->userInfoTableWidget->rowCount(); ++i) {
        if (ui->userInfoTableWidget->item(i, 0)->checkState()) {
            infoList << i;
        }
    }

    if (infoList.isEmpty()) {
        infoWindow("请选择需要删除的用户!");
        return;
    }

    if (questionWindow("确定删除该用户吗?") == QMessageBox::No) {
        infoWindow("您已取消删除该用户!");
        return;
    }

    for (int i = 0; i < infoList.size(); ++i) {
        userTel = ui->userInfoTableWidget->item(infoList.at(i), 3)->text();
        userName = ui->userInfoTableWidget->item(infoList.at(i), 1)->text();

        QSqlTableModel *userInfoModel = new QSqlTableModel(this);
        userInfoModel->setTable("user_info");
        userInfoModel->setFilter(tr("u_tel = '%1'").arg(userTel));
        userInfoModel->select();

        if (userInfoModel->rowCount() == 1) {
            auto deleteInfo =
                tr("DELETE FROM user_info WHERE u_tel = '%1'").arg(userTel);

            QSqlQuery deleteQuery;
            if (deleteQuery.exec(deleteInfo)) {
                infoWindow(tr("删除用户%1成功!").arg(userName));
                clearUserInfoTable();
                ui->userTelLineEdit->clear();
                ui->userTelLineEdit->setFocus();
            } else {
                infoWindow(tr("删除用户%1失败!").arg(userName));
            }
        }

        delete userInfoModel;
    }
}

