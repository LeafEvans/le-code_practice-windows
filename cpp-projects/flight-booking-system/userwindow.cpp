#include "userwindow.h"

#include "logindialog.h"
#include "ui_userwindow.h"

QString curUserTelNum;  // 当前用户手机号码

UserWindow::UserWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::UserWindow) {
  ui->setupUi(this);
  initUserWindow();
  initUserInfo();
}

UserWindow::~UserWindow() { delete ui; }

void UserWindow::paintEvent(QPaintEvent *event) {
  QPainter userWindowPainter(this);
  userWindowPainter.setOpacity(0.5);
  userWindowPainter.drawPixmap(0, 0, this->width(), this->height(),
                               QPixmap(":/image/user_background.jpg"));
}

void UserWindow::initUserWindow() {
    setWindowTitle("用户机票管理");
    setWindowIcon(QIcon(":/image/user.svg"));

    ui->oneWayRadioButton->setChecked(true);
    ui->flightDateEdit->setCalendarPopup(true);
    ui->flightDateEdit->setDate(QDate::currentDate());

    ui->flightQueryTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->orderCenterTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->persCenterTableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->flightNumLineEdit->setReadOnly(true);
    ui->flightDateEdit->setReadOnly(true);

    if (ui->chDepCityComboBox->currentText() == "热门") {
        ui->depCityComboBox->insertItem(0, "北京");
        ui->depCityComboBox->insertItem(1, "上海");
        ui->depCityComboBox->insertItem(2, "广州");
        ui->depCityComboBox->insertItem(3, "深圳");
        ui->depCityComboBox->insertItem(4, "成都");
        ui->depCityComboBox->insertItem(5, "杭州");
        ui->depCityComboBox->insertItem(6, "西安");
        ui->depCityComboBox->insertItem(7, "重庆");
        ui->depCityComboBox->insertItem(8, "青岛");
        ui->depCityComboBox->insertItem(9, "南京");
        ui->depCityComboBox->insertItem(10, "厦门");
        ui->depCityComboBox->insertItem(11, "昆明");
        ui->depCityComboBox->insertItem(12, "大连");
        ui->depCityComboBox->insertItem(13, "天津");
        ui->depCityComboBox->insertItem(14, "郑州");
        ui->depCityComboBox->insertItem(15, "三亚");
        ui->depCityComboBox->insertItem(16, "济南");
        ui->depCityComboBox->insertItem(17, "福州");
        ui->depCityComboBox->insertItem(18, "长沙");
    }

    if (ui->chArrCityComboBox->currentText() == "热门") {
        ui->arrCityComboBox->insertItem(0, "北京");
        ui->arrCityComboBox->insertItem(1, "上海");
        ui->arrCityComboBox->insertItem(2, "广州");
        ui->arrCityComboBox->insertItem(3, "深圳");
        ui->arrCityComboBox->insertItem(4, "成都");
        ui->arrCityComboBox->insertItem(5, "杭州");
        ui->arrCityComboBox->insertItem(6, "西安");
        ui->arrCityComboBox->insertItem(7, "重庆");
        ui->arrCityComboBox->insertItem(8, "青岛");
        ui->arrCityComboBox->insertItem(9, "南京");
        ui->arrCityComboBox->insertItem(10, "厦门");
        ui->arrCityComboBox->insertItem(11, "昆明");
        ui->arrCityComboBox->insertItem(12, "大连");
        ui->arrCityComboBox->insertItem(13, "天津");
        ui->arrCityComboBox->insertItem(14, "郑州");
        ui->arrCityComboBox->insertItem(15, "三亚");
        ui->arrCityComboBox->insertItem(16, "济南");
        ui->arrCityComboBox->insertItem(17, "福州");
        ui->arrCityComboBox->insertItem(18, "长沙");
    }
}


void UserWindow::initUserInfo() {
    userTel = curUserTelNum;

    QSqlTableModel userInfoModel(this);

    userInfoModel.setTable("user_info");
    userInfoModel.setFilter(tr("u_tel = '%1'").arg(userTel));
    userInfoModel.select();

    if (userInfoModel.rowCount() == 1) {
        userName = userInfoModel.data(userInfoModel.index(0, 0)).toString();
    }

    qDebug() << userName;
}


void UserWindow::clearFlightQueryTable() {
    ui->flightQueryTableWidget->clearContents();
    ui->flightQueryTableWidget->setRowCount(0);
}

void UserWindow::clearOrderCenterTable() {
    ui->orderCenterTableWidget->clearContents();
    ui->orderCenterTableWidget->setRowCount(0);
}

void UserWindow::clearPersCenterTable() {
    ui->persCenterTableWidget->clearContents();
    ui->persCenterTableWidget->setRowCount(0);
}

void UserWindow::on_persCenterPushButton_clicked() {
    persCenterShow();
    ui->stackedWidget->setCurrentWidget(ui->persCenterPage);
}

void UserWindow::on_orderCenterPushButton_clicked() {
    orderCenterShow();
    ui->stackedWidget->setCurrentWidget(ui->orderCenterPage);
}

void UserWindow::on_flightQueryPushButton_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->flightQueryPage);
}

void UserWindow::on_exitPushButton_clicked() {
    if (questionWindow("确定退出系统吗?") == QMessageBox::Yes) {
        this->close();
        LoginDialog *loginDialog = new LoginDialog;
        loginDialog->show();
    }
}


void UserWindow::on_oneWayRadioButton_clicked() {
    ui->flightModePushButton->setText(tr("单程城市航班查询"));
    ui->flightNumLineEdit->setReadOnly(true);
    ui->flightDateEdit->setReadOnly(false);
    ui->depCityComboBox->setEnabled(true);
    ui->arrCityComboBox->setEnabled(true);
    ui->flightNumLineEdit->clear();
    ui->flightDateEdit->clear();
    clearFlightQueryTable();
}

void UserWindow::on_twoWayRadioButton_clicked() {
    ui->flightModePushButton->setText(tr("双程城市航班查询"));
    ui->flightNumLineEdit->setReadOnly(true);
    ui->flightDateEdit->setReadOnly(false);
    ui->depCityComboBox->setEnabled(true);
    ui->arrCityComboBox->setEnabled(true);
    ui->flightNumLineEdit->clear();
    ui->flightDateEdit->clear();
    clearFlightQueryTable();
}

void UserWindow::on_flightNumRadioButton_clicked() {
    ui->flightModePushButton->setText(tr("航班号查询"));
    ui->flightNumLineEdit->setReadOnly(false);
    ui->flightDateEdit->setReadOnly(true);
    ui->depCityComboBox->setEnabled(false);
    ui->arrCityComboBox->setEnabled(false);
    ui->flightNumLineEdit->clear();
    ui->flightDateEdit->clear();
    clearFlightQueryTable();
}

void UserWindow::on_flightDateRadioButton_clicked() {
    ui->flightModePushButton->setText(tr("航班日期查询"));
    ui->flightNumLineEdit->setReadOnly(true);
    ui->flightDateEdit->setReadOnly(false);
    ui->depCityComboBox->setEnabled(false);
    ui->arrCityComboBox->setEnabled(false);
    ui->flightNumLineEdit->clear();
    ui->flightDateEdit->clear();
    clearFlightQueryTable();
}

void UserWindow::on_flightModePushButton_clicked() {
  ui->flightQueryTableWidget->setEditTriggers(
      QAbstractItemView::NoEditTriggers);
  ui->flightQueryTableWidget->setSelectionBehavior(
      QAbstractItemView::SelectRows);

  auto infoText = ui->flightQueryPushButton->text();

  if (infoText == "单程城市航班查询" || infoText == "双程城市航班查询") {
    flightCityQuery();
  } else if (infoText == "航班号查询") {
    flightNumQuery();
  } else if (infoText == "航班日期查询") {
    flightDateQuery();
  }
}

void UserWindow::on_bookingPushButton_clicked() {
    QList<int> selectedRows;

    // Collect the row indices of the selected items.
    for (int i = 0; i < ui->flightQueryTableWidget->rowCount(); ++i) {
        QTableWidgetItem *item = ui->flightQueryTableWidget->item(i, 0);
        if (item && item->checkState() == Qt::Checked) {
            selectedRows.append(i);
        }
    }

    if (selectedRows.isEmpty()) {
        QMessageBox::information(this, "", tr("请选择要订票的航班!"));
        return;
    }

    QDateTime currentDateTime(QDateTime::currentDateTime());
    QString currentDate = currentDateTime.date().toString("yyyyMMdd");
    QString currentTime = currentDateTime.time().toString("hhmmss");

    // Process each selected row.
    for (int index : selectedRows) {
        QTableWidgetItem *item;

        item = ui->flightQueryTableWidget->item(index, 1);
        QString orderFlightNum = item->text();

        item = ui->flightQueryTableWidget->item(index, 2);
        QString orderFlightPrice = item->text();

        item = ui->flightQueryTableWidget->item(index, 3);
        QString orderFlightDate = item->text();

        item = ui->flightQueryTableWidget->item(index, 5);
        QString orderFlightTime = item->text();

        item = ui->flightQueryTableWidget->item(index, 8);
        QString orderFlightDepCity = item->text();

        item = ui->flightQueryTableWidget->item(index, 9);
        QString orderFlightArrCity = item->text();

        QString orderPayState = "未支付";
        QString orderNum = userTel + currentDate + currentTime;

        // Assuming userName and userTel are member variables of UserWindow.
        QString orderUserName = userName;
        QString orderUserTel = userTel;

        QString orderInfo = QString(
                                "INSERT INTO order_info "
                                "(order_num, order_flight_num, order_u_tel, "
                                "order_u_name, order_pay_state, order_flight_date, "
                                "order_flight_time, order_flight_dep_city, order_flight_arr_city, "
                                "order_flight_price, order_time) "
                                "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11')"
                                ).arg(orderNum, orderFlightNum, orderUserTel, orderUserName, orderPayState,
                                     orderFlightDate, orderFlightTime, orderFlightDepCity, orderFlightArrCity,
                                     orderFlightPrice, currentTime);

        QSqlQuery query;
        if (query.exec(orderInfo)) {
            QMessageBox::information(this, "", tr("订单 %1 下单成功, 可到订单中心查看订单!").arg(orderNum));
            ui->flightQueryTableWidget->item(index, 0)->setCheckState(Qt::Unchecked);
        } else {
            QMessageBox::warning(this, "", tr("下单失败!"));
        }
    }
}

void UserWindow::flightCityQuery() {
    clearFlightQueryTable();

    QString depCity = ui->depCityComboBox->currentText();
    QString arrCity = ui->arrCityComboBox->currentText();

    if (depCity.isEmpty() || arrCity.isEmpty()) {
        infoWindow("请选择始发地及目的地!");
        return;
    }

    QSqlTableModel flightModel;
    flightModel.setTable("flight_info");

    QString filter = QString("f_dep_city = '%1' AND f_arr_city = '%2'").arg(depCity, arrCity);
    flightModel.setFilter(filter);
    flightModel.select();

    if (flightModel.rowCount() < 1) {
        if (ui->flightQueryPushButton->text() == "单程城市航班查询") {
            infoWindow("未查询到单程城市相关航班信息!");
        } else {
            infoWindow("未查询到双程城市相关航班信息!");
        }
        return;
    }

    int rowCount = flightModel.rowCount();
    ui->flightQueryTableWidget->setRowCount(rowCount);

    for (int i = 0; i < rowCount; ++i) {
        QStringList rowData;
        for (int col = 0; col < flightModel.columnCount(); ++col) {
            rowData << flightModel.data(flightModel.index(i, col)).toString();
        }

        for (int col = 0; col < rowData.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(rowData.at(col));
            ui->flightQueryTableWidget->setItem(i, col + 1, item);
        }

        // Adding check box in the first column
        auto *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        ui->flightQueryTableWidget->setItem(i, 0, check);
    }
}



void UserWindow::flightNumQuery() {
    QString flightNum = ui->flightNumLineEdit->text();

    if (flightNum.isEmpty()) {
        infoWindow("请输入航班号!");
        return;
    }

    QSqlTableModel flightNumModel;
    flightNumModel.setTable("flight_info");
    flightNumModel.setFilter(tr("f_num = '%1'").arg(flightNum));
    flightNumModel.select();

    if (flightNumModel.rowCount() != 1) {
        infoWindow("未查询到该航班相关信息!");
        ui->flightNumLineEdit->clear();
        ui->flightNumLineEdit->setFocus();
        clearFlightQueryTable();
        return;
    }

    QStringList rowData;
    for (int col = 0; col < flightNumModel.columnCount(); ++col) {
        rowData << flightNumModel.data(flightNumModel.index(0, col)).toString();
    }

    int rowCount = ui->flightQueryTableWidget->rowCount();
    ui->flightQueryTableWidget->insertRow(rowCount);

    for (int col = 0; col < rowData.size(); ++col) {
        QTableWidgetItem *item = new QTableWidgetItem(rowData.at(col));
        ui->flightQueryTableWidget->setItem(rowCount, col + 1, item);
    }

    auto *check = new QTableWidgetItem();
    check->setCheckState(Qt::Unchecked);
    ui->flightQueryTableWidget->setItem(rowCount, 0, check);
}


void UserWindow::flightDateQuery() {
    QString flightDepDate = ui->flightDateEdit->date().toString("yyyy-MM-dd");

    auto flightDateModel = new QSqlTableModel();
    flightDateModel->setTable("flight_info");
    flightDateModel->setFilter(tr("f_dep_date = '%1'").arg(flightDepDate));
    flightDateModel->select();

    if (flightDateModel->rowCount() < 1) {
        infoWindow("未查询到该日期相关航班日期!");
        clearFlightQueryTable();
        return;
    }

    clearFlightQueryTable();

    for (int i = 0; i < flightDateModel->rowCount(); ++i) {        QStringList rowData;
        for (int col = 0; col < flightDateModel->columnCount(); ++col) {
            rowData << flightDateModel->data(flightDateModel->index(i, col)).toString();
        }

        int rowCount = ui->flightQueryTableWidget->rowCount();
        ui->flightQueryTableWidget->insertRow(rowCount);

        auto *check = new QTableWidgetItem;
        check->setCheckState(Qt::Unchecked);
        ui->flightQueryTableWidget->setItem(rowCount, 0, check);

        for (int col = 0; col < rowData.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(rowData.at(col));
            ui->flightQueryTableWidget->setItem(rowCount, col + 1, item);
        }
    }

    delete flightDateModel;
}


void UserWindow::persCenterShow() {
    clearPersCenterTable();

    ui->persCenterTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->persCenterTableWidget->horizontalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->persCenterTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QSqlTableModel persCenterModel;
    persCenterModel.setTable("ele_ticket");
    persCenterModel.setFilter(QString("e_ticket_u_name = '%1'").arg(userName));
    persCenterModel.select();

    if (persCenterModel.rowCount() < 1) {
        infoWindow("未查询到您的相关机票信息!");
        return;
    }

    int rowCount = persCenterModel.rowCount();
    ui->persCenterTableWidget->setRowCount(rowCount);

    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem *itemTicketNum = new QTableWidgetItem(persCenterModel.data(persCenterModel.index(i, 0)).toString());
        QTableWidgetItem *itemUserName = new QTableWidgetItem(persCenterModel.data(persCenterModel.index(i, 2)).toString());
        QTableWidgetItem *itemFlightNum = new QTableWidgetItem(persCenterModel.data(persCenterModel.index(i, 3)).toString());
        QTableWidgetItem *itemDepCity = new QTableWidgetItem(persCenterModel.data(persCenterModel.index(i, 4)).toString());
        QTableWidgetItem *itemArrCity = new QTableWidgetItem(persCenterModel.data(persCenterModel.index(i, 5)).toString());
        QTableWidgetItem *itemDepDate = new QTableWidgetItem(persCenterModel.data(persCenterModel.index(i, 6)).toString());
        QTableWidgetItem *itemDepTime = new QTableWidgetItem(persCenterModel.data(persCenterModel.index(i, 7)).toString());
        QTableWidgetItem *itemFlightPrice = new QTableWidgetItem(persCenterModel.data(persCenterModel.index(i, 8)).toString());

        ui->persCenterTableWidget->setItem(i, 0, itemTicketNum);
        ui->persCenterTableWidget->setItem(i, 1, itemUserName);
        ui->persCenterTableWidget->setItem(i, 2, itemFlightNum);
        ui->persCenterTableWidget->setItem(i, 3, itemDepCity);
        ui->persCenterTableWidget->setItem(i, 4, itemArrCity);
        ui->persCenterTableWidget->setItem(i, 5, itemDepDate);
        ui->persCenterTableWidget->setItem(i, 6, itemDepTime);
        ui->persCenterTableWidget->setItem(i, 7, itemFlightPrice);
    }
}


void UserWindow::orderCenterShow() {
  clearOrderCenterTable();

  ui->orderCenterTableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->orderCenterTableWidget->horizontalHeader()->setEditTriggers(
      QAbstractItemView::NoEditTriggers);
  ui->orderCenterTableWidget->setSelectionBehavior(
      QAbstractItemView::SelectRows);

  QSqlTableModel orderCenterModel;
  orderCenterModel.setTable("order_info");
  orderCenterModel.setFilter(tr("order_u_name = '%1'").arg(userName));
  orderCenterModel.select();

  if (!(orderCenterModel.rowCount() >= 1)) {
    infoWindow("未查询到您的相关订单信息!");
    return;
  }

  for (int i = 0; i < orderCenterModel.rowCount(); ++i) {
    orderNum = orderCenterModel.data(orderCenterModel.index(i, 0)).toString();
    orderFlightNum =
        orderCenterModel.data(orderCenterModel.index(i, 1)).toString();
    orderUserTel =
        orderCenterModel.data(orderCenterModel.index(i, 2)).toString();
    orderUserName =
        orderCenterModel.data(orderCenterModel.index(i, 3)).toString();
    orderPayState =
        orderCenterModel.data(orderCenterModel.index(i, 4)).toString();
    orderFlightDate =
        orderCenterModel.data(orderCenterModel.index(i, 5)).toString();
    orderFlightTime =
        orderCenterModel.data(orderCenterModel.index(i, 6)).toString();
    orderFlightDepCity =
        orderCenterModel.data(orderCenterModel.index(i, 7)).toString();
    orderFlightArrCity =
        orderCenterModel.data(orderCenterModel.index(i, 8)).toString();
    orderFlightPrice =
        orderCenterModel.data(orderCenterModel.index(i, 9)).toString();
    orderTime = orderCenterModel.data(orderCenterModel.index(i, 10)).toString();
    orderPayTime =
        orderCenterModel.data(orderCenterModel.index(i, 11)).toString();

    int rowCount = ui->orderCenterTableWidget->rowCount();
    ui->orderCenterTableWidget->insertRow(rowCount);

    auto *check = new QTableWidgetItem();
    check->setCheckState(Qt::Unchecked);
    ui->orderCenterTableWidget->setItem(rowCount, 0, check);
    ui->orderCenterTableWidget->setItem(rowCount, 1,
                                        new QTableWidgetItem(orderNum));
    ui->orderCenterTableWidget->setItem(rowCount, 2,
                                        new QTableWidgetItem(orderFlightNum));
    ui->orderCenterTableWidget->setItem(rowCount, 3,
                                        new QTableWidgetItem(orderUserTel));
    ui->orderCenterTableWidget->setItem(rowCount, 4,
                                        new QTableWidgetItem(orderUserName));
    ui->orderCenterTableWidget->setItem(rowCount, 5,
                                        new QTableWidgetItem(orderPayState));
    ui->orderCenterTableWidget->setItem(rowCount, 6,
                                        new QTableWidgetItem(orderFlightDate));
    ui->orderCenterTableWidget->setItem(rowCount, 7,
                                        new QTableWidgetItem(orderFlightTime));
    ui->orderCenterTableWidget->setItem(
        rowCount, 8, new QTableWidgetItem(orderFlightDepCity));
    ui->orderCenterTableWidget->setItem(
        rowCount, 9, new QTableWidgetItem(orderFlightArrCity));
    ui->orderCenterTableWidget->setItem(rowCount, 10,
                                        new QTableWidgetItem(orderFlightPrice));
    ui->orderCenterTableWidget->setItem(rowCount, 11,
                                        new QTableWidgetItem(orderTime));
    ui->orderCenterTableWidget->setItem(rowCount, 12,
                                        new QTableWidgetItem(orderPayTime));
  }
}

void UserWindow::on_chDepCityComboBox_textActivated(const QString &arg1) {
  ui->depCityComboBox->clear();

  if (arg1 == "热门") {
    ui->depCityComboBox->insertItem(0, "北京");
    ui->depCityComboBox->insertItem(1, "上海");
    ui->depCityComboBox->insertItem(2, "广州");
    ui->depCityComboBox->insertItem(3, "深圳");
    ui->depCityComboBox->insertItem(4, "成都");
    ui->depCityComboBox->insertItem(5, "杭州");
    ui->depCityComboBox->insertItem(6, "西安");
    ui->depCityComboBox->insertItem(7, "重庆");
    ui->depCityComboBox->insertItem(8, "青岛");
    ui->depCityComboBox->insertItem(9, "南京");
    ui->depCityComboBox->insertItem(10, "厦门");
    ui->depCityComboBox->insertItem(11, "昆明");
    ui->depCityComboBox->insertItem(12, "大连");
    ui->depCityComboBox->insertItem(13, "天津");
    ui->depCityComboBox->insertItem(14, "郑州");
    ui->depCityComboBox->insertItem(15, "三亚");
    ui->depCityComboBox->insertItem(16, "济南");
    ui->depCityComboBox->insertItem(17, "福州");
    ui->depCityComboBox->insertItem(18, "长沙");
  } else if (arg1 == "ABCDE") {
    ui->depCityComboBox->insertItem(0, "阿尔山");
    ui->depCityComboBox->insertItem(1, "阿克苏");
    ui->depCityComboBox->insertItem(2, "阿拉善右旗");
    ui->depCityComboBox->insertItem(3, "阿拉善左旗");
    ui->depCityComboBox->insertItem(4, "阿勒泰");
    ui->depCityComboBox->insertItem(5, "阿里");
    ui->depCityComboBox->insertItem(6, "澳门");
    ui->depCityComboBox->insertItem(7, "安庆");
    ui->depCityComboBox->insertItem(8, "安顺");
    ui->depCityComboBox->insertItem(9, "鞍山");
    ui->depCityComboBox->insertItem(10, "巴彦淖尔");
    ui->depCityComboBox->insertItem(11, "百色");
    ui->depCityComboBox->insertItem(12, "包头");
    ui->depCityComboBox->insertItem(13, "保山");
    ui->depCityComboBox->insertItem(14, "北海");
    ui->depCityComboBox->insertItem(15, "北京");
    ui->depCityComboBox->insertItem(16, "白城");
    ui->depCityComboBox->insertItem(17, "白山");
    ui->depCityComboBox->insertItem(18, "毕节");
    ui->depCityComboBox->insertItem(19, "博乐");
    ui->depCityComboBox->insertItem(20, "重庆");
    ui->depCityComboBox->insertItem(21, "昌都");
    ui->depCityComboBox->insertItem(22, "常德");
    ui->depCityComboBox->insertItem(23, "常州");
    ui->depCityComboBox->insertItem(24, "朝阳");
    ui->depCityComboBox->insertItem(25, "成都");
    ui->depCityComboBox->insertItem(26, "池州");
    ui->depCityComboBox->insertItem(27, "赤峰");
    ui->depCityComboBox->insertItem(28, "长春");
    ui->depCityComboBox->insertItem(29, "长沙");
    ui->depCityComboBox->insertItem(30, "长治");
    ui->depCityComboBox->insertItem(31, "承德");
    ui->depCityComboBox->insertItem(32, "沧源");
    ui->depCityComboBox->insertItem(33, "达县");
    ui->depCityComboBox->insertItem(34, "大理");
    ui->depCityComboBox->insertItem(35, "大连");
    ui->depCityComboBox->insertItem(36, "大庆");
    ui->depCityComboBox->insertItem(37, "大同");
    ui->depCityComboBox->insertItem(38, "丹东");
    ui->depCityComboBox->insertItem(39, "稻城");
    ui->depCityComboBox->insertItem(40, "东营");
    ui->depCityComboBox->insertItem(41, "敦煌");
  } else if (arg1 == "FGHIJ") {
    ui->depCityComboBox->insertItem(0, "佛山");
    ui->depCityComboBox->insertItem(1, "福州");
    ui->depCityComboBox->insertItem(2, "抚远");
    ui->depCityComboBox->insertItem(3, "阜阳");
    ui->depCityComboBox->insertItem(4, "赣州");
    ui->depCityComboBox->insertItem(5, "格尔木");
    ui->depCityComboBox->insertItem(6, "固原");
    ui->depCityComboBox->insertItem(7, "广元");
    ui->depCityComboBox->insertItem(8, "广州");
    ui->depCityComboBox->insertItem(9, "贵阳");
    ui->depCityComboBox->insertItem(10, "桂林");
    ui->depCityComboBox->insertItem(11, "哈尔滨");
    ui->depCityComboBox->insertItem(12, "哈密");
    ui->depCityComboBox->insertItem(13, "海口");
    ui->depCityComboBox->insertItem(14, "海拉尔");
    ui->depCityComboBox->insertItem(15, "邯郸");
    ui->depCityComboBox->insertItem(16, "汉中");
    ui->depCityComboBox->insertItem(17, "杭州");
    ui->depCityComboBox->insertItem(18, "合肥");
    ui->depCityComboBox->insertItem(19, "和田");
    ui->depCityComboBox->insertItem(20, "黑河");
    ui->depCityComboBox->insertItem(21, "呼和浩特");
    ui->depCityComboBox->insertItem(22, "淮安");
    ui->depCityComboBox->insertItem(23, "怀化");
    ui->depCityComboBox->insertItem(24, "黄山");
    ui->depCityComboBox->insertItem(25, "惠州");
    ui->depCityComboBox->insertItem(26, "鸡西");
    ui->depCityComboBox->insertItem(27, "济南");
    ui->depCityComboBox->insertItem(28, "济宁");
    ui->depCityComboBox->insertItem(29, "加格达奇");
    ui->depCityComboBox->insertItem(30, "佳木斯");
    ui->depCityComboBox->insertItem(31, "嘉峪关");
    ui->depCityComboBox->insertItem(32, "揭阳");
    ui->depCityComboBox->insertItem(33, "金昌");
    ui->depCityComboBox->insertItem(34, "金门");
    ui->depCityComboBox->insertItem(35, "锦州");
    ui->depCityComboBox->insertItem(36, "嘉义");
    ui->depCityComboBox->insertItem(37, "西双版纳");
    ui->depCityComboBox->insertItem(38, "建三江");
    ui->depCityComboBox->insertItem(39, "晋江");
    ui->depCityComboBox->insertItem(40, "井冈山");
    ui->depCityComboBox->insertItem(41, "景德镇");
    ui->depCityComboBox->insertItem(42, "九江");
    ui->depCityComboBox->insertItem(43, "九寨沟");
  } else if (arg1 == "KLMN") {
    ui->depCityComboBox->insertItem(0, "喀什");
    ui->depCityComboBox->insertItem(1, "凯里");
    ui->depCityComboBox->insertItem(2, "康定");
    ui->depCityComboBox->insertItem(3, "克拉玛依");
    ui->depCityComboBox->insertItem(4, "库车");
    ui->depCityComboBox->insertItem(5, "库尔勒");
    ui->depCityComboBox->insertItem(6, "昆明");
    ui->depCityComboBox->insertItem(7, "拉萨");
    ui->depCityComboBox->insertItem(8, "兰州");
    ui->depCityComboBox->insertItem(9, "黎平");
    ui->depCityComboBox->insertItem(10, "丽江");
    ui->depCityComboBox->insertItem(11, "荔波");
    ui->depCityComboBox->insertItem(12, "连云港");
    ui->depCityComboBox->insertItem(13, "六盘水");
    ui->depCityComboBox->insertItem(14, "临汾");
    ui->depCityComboBox->insertItem(15, "林芝");
    ui->depCityComboBox->insertItem(16, "临沧");
    ui->depCityComboBox->insertItem(17, "临沂");
    ui->depCityComboBox->insertItem(18, "柳州");
    ui->depCityComboBox->insertItem(19, "泸州");
    ui->depCityComboBox->insertItem(20, "洛阳");
    ui->depCityComboBox->insertItem(21, "吕梁");
    ui->depCityComboBox->insertItem(22, "澜沧");
    ui->depCityComboBox->insertItem(23, "龙岩");
    ui->depCityComboBox->insertItem(24, "满洲里");
    ui->depCityComboBox->insertItem(25, "芒市");
    ui->depCityComboBox->insertItem(26, "梅州");
    ui->depCityComboBox->insertItem(27, "绵阳");
    ui->depCityComboBox->insertItem(28, "漠河");
    ui->depCityComboBox->insertItem(29, "牡丹江");
    ui->depCityComboBox->insertItem(30, "马祖");
    ui->depCityComboBox->insertItem(31, "南昌");
    ui->depCityComboBox->insertItem(32, "南充");
    ui->depCityComboBox->insertItem(33, "南京");
    ui->depCityComboBox->insertItem(34, "南宁");
    ui->depCityComboBox->insertItem(35, "南通");
    ui->depCityComboBox->insertItem(36, "南阳");
    ui->depCityComboBox->insertItem(37, "宁波");
    ui->depCityComboBox->insertItem(38, "宁蒗");
  } else if (arg1 == "OPQR") {
    ui->depCityComboBox->insertItem(0, "攀枝花");
    ui->depCityComboBox->insertItem(1, "普洱");
    ui->depCityComboBox->insertItem(2, "齐齐哈尔");
    ui->depCityComboBox->insertItem(3, "黔江");
    ui->depCityComboBox->insertItem(4, "且末");
    ui->depCityComboBox->insertItem(5, "秦皇岛");
    ui->depCityComboBox->insertItem(6, "青岛");
    ui->depCityComboBox->insertItem(7, "庆阳");
    ui->depCityComboBox->insertItem(8, "衢州");
    ui->depCityComboBox->insertItem(9, "日喀则");
    ui->depCityComboBox->insertItem(10, "日照");
  } else if (arg1 == "STUV") {
    ui->depCityComboBox->insertItem(0, "三亚");
    ui->depCityComboBox->insertItem(1, "上海");
    ui->depCityComboBox->insertItem(2, "深圳");
    ui->depCityComboBox->insertItem(3, "神农架");
    ui->depCityComboBox->insertItem(4, "沈阳");
    ui->depCityComboBox->insertItem(5, "石家庄");
    ui->depCityComboBox->insertItem(6, "塔城");
    ui->depCityComboBox->insertItem(7, "台州");
    ui->depCityComboBox->insertItem(8, "太原");
    ui->depCityComboBox->insertItem(9, "扬州");
    ui->depCityComboBox->insertItem(10, "唐山");
    ui->depCityComboBox->insertItem(11, "腾冲");
    ui->depCityComboBox->insertItem(12, "天津");
    ui->depCityComboBox->insertItem(13, "天水");
    ui->depCityComboBox->insertItem(14, "通辽");
    ui->depCityComboBox->insertItem(15, "铜仁");
    ui->depCityComboBox->insertItem(16, "吐鲁番");
  } else if (arg1 == "WXYZ") {
    ui->depCityComboBox->insertItem(0, "万州");
    ui->depCityComboBox->insertItem(1, "威海");
    ui->depCityComboBox->insertItem(2, "潍坊");
    ui->depCityComboBox->insertItem(3, "温州");
    ui->depCityComboBox->insertItem(4, "文山");
    ui->depCityComboBox->insertItem(5, "乌海");
    ui->depCityComboBox->insertItem(6, "乌兰浩特");
    ui->depCityComboBox->insertItem(7, "乌鲁木齐");
    ui->depCityComboBox->insertItem(8, "无锡");
    ui->depCityComboBox->insertItem(9, "梧州");
    ui->depCityComboBox->insertItem(10, "武汉");
    ui->depCityComboBox->insertItem(11, "武夷山");
    ui->depCityComboBox->insertItem(12, "西安");
    ui->depCityComboBox->insertItem(13, "西昌");
    ui->depCityComboBox->insertItem(14, "西宁");
    ui->depCityComboBox->insertItem(15, "锡林浩特");
    ui->depCityComboBox->insertItem(16, "厦门");
    ui->depCityComboBox->insertItem(17, "香格里拉");
    ui->depCityComboBox->insertItem(18, "襄阳");
    ui->depCityComboBox->insertItem(19, "兴义");
    ui->depCityComboBox->insertItem(20, "徐州");
    ui->depCityComboBox->insertItem(21, "香港");
    ui->depCityComboBox->insertItem(22, "烟台");
    ui->depCityComboBox->insertItem(23, "延安");
    ui->depCityComboBox->insertItem(24, "延吉");
    ui->depCityComboBox->insertItem(25, "盐城");
    ui->depCityComboBox->insertItem(26, "伊春");
    ui->depCityComboBox->insertItem(27, "伊宁");
    ui->depCityComboBox->insertItem(28, "宜宾");
    ui->depCityComboBox->insertItem(29, "宜昌");
    ui->depCityComboBox->insertItem(30, "宜春");
    ui->depCityComboBox->insertItem(31, "义乌");
    ui->depCityComboBox->insertItem(32, "银川");
    ui->depCityComboBox->insertItem(33, "永州");
    ui->depCityComboBox->insertItem(34, "榆林");
    ui->depCityComboBox->insertItem(35, "玉树");
    ui->depCityComboBox->insertItem(36, "运城");
    ui->depCityComboBox->insertItem(37, "湛江");
    ui->depCityComboBox->insertItem(38, "张家界");
    ui->depCityComboBox->insertItem(39, "张家口");
    ui->depCityComboBox->insertItem(40, "张掖");
    ui->depCityComboBox->insertItem(41, "昭通");
    ui->depCityComboBox->insertItem(42, "郑州");
    ui->depCityComboBox->insertItem(43, "中卫");
    ui->depCityComboBox->insertItem(44, "舟山");
    ui->depCityComboBox->insertItem(45, "珠海");
    ui->depCityComboBox->insertItem(46, "遵义");
  }
}

void UserWindow::on_chArrCityComboBox_textActivated(const QString &arg1) {
  ui->arrCityComboBox->clear();

  if (arg1 == "热门") {
    ui->arrCityComboBox->insertItem(0, "北京");
    ui->arrCityComboBox->insertItem(1, "上海");
    ui->arrCityComboBox->insertItem(2, "广州");
    ui->arrCityComboBox->insertItem(3, "深圳");
    ui->arrCityComboBox->insertItem(4, "成都");
    ui->arrCityComboBox->insertItem(5, "杭州");
    ui->arrCityComboBox->insertItem(6, "西安");
    ui->arrCityComboBox->insertItem(7, "重庆");
    ui->arrCityComboBox->insertItem(8, "青岛");
    ui->arrCityComboBox->insertItem(9, "南京");
    ui->arrCityComboBox->insertItem(10, "厦门");
    ui->arrCityComboBox->insertItem(11, "昆明");
    ui->arrCityComboBox->insertItem(12, "大连");
    ui->arrCityComboBox->insertItem(13, "天津");
    ui->arrCityComboBox->insertItem(14, "郑州");
    ui->arrCityComboBox->insertItem(15, "三亚");
    ui->arrCityComboBox->insertItem(16, "济南");
    ui->arrCityComboBox->insertItem(17, "福州");
    ui->arrCityComboBox->insertItem(18, "长沙");
  } else if (arg1 == "ABCDE") {
    ui->arrCityComboBox->insertItem(0, "阿尔山");
    ui->arrCityComboBox->insertItem(1, "阿克苏");
    ui->arrCityComboBox->insertItem(2, "阿拉善右旗");
    ui->arrCityComboBox->insertItem(3, "阿拉善左旗");
    ui->arrCityComboBox->insertItem(4, "阿勒泰");
    ui->arrCityComboBox->insertItem(5, "阿里");
    ui->arrCityComboBox->insertItem(6, "澳门");
    ui->arrCityComboBox->insertItem(7, "安庆");
    ui->arrCityComboBox->insertItem(8, "安顺");
    ui->arrCityComboBox->insertItem(9, "鞍山");
    ui->arrCityComboBox->insertItem(10, "巴彦淖尔");
    ui->arrCityComboBox->insertItem(11, "百色");
    ui->arrCityComboBox->insertItem(12, "包头");
    ui->arrCityComboBox->insertItem(13, "保山");
    ui->arrCityComboBox->insertItem(14, "北海");
    ui->arrCityComboBox->insertItem(15, "北京");
    ui->arrCityComboBox->insertItem(16, "白城");
    ui->arrCityComboBox->insertItem(17, "白山");
    ui->arrCityComboBox->insertItem(18, "毕节");
    ui->arrCityComboBox->insertItem(19, "博乐");
    ui->arrCityComboBox->insertItem(20, "重庆");
    ui->arrCityComboBox->insertItem(21, "昌都");
    ui->arrCityComboBox->insertItem(22, "常德");
    ui->arrCityComboBox->insertItem(23, "常州");
    ui->arrCityComboBox->insertItem(24, "朝阳");
    ui->arrCityComboBox->insertItem(25, "成都");
    ui->arrCityComboBox->insertItem(26, "池州");
    ui->arrCityComboBox->insertItem(27, "赤峰");
    ui->arrCityComboBox->insertItem(28, "长春");
    ui->arrCityComboBox->insertItem(29, "长沙");
    ui->arrCityComboBox->insertItem(30, "长治");
    ui->arrCityComboBox->insertItem(31, "承德");
    ui->arrCityComboBox->insertItem(32, "沧源");
    ui->arrCityComboBox->insertItem(33, "达县");
    ui->arrCityComboBox->insertItem(34, "大理");
    ui->arrCityComboBox->insertItem(35, "大连");
    ui->arrCityComboBox->insertItem(36, "大庆");
    ui->arrCityComboBox->insertItem(37, "大同");
    ui->arrCityComboBox->insertItem(38, "丹东");
    ui->arrCityComboBox->insertItem(39, "稻城");
    ui->arrCityComboBox->insertItem(40, "东营");
    ui->arrCityComboBox->insertItem(41, "敦煌");
  } else if (arg1 == "FGHIJ") {
    ui->arrCityComboBox->insertItem(0, "佛山");
    ui->arrCityComboBox->insertItem(1, "福州");
    ui->arrCityComboBox->insertItem(2, "抚远");
    ui->arrCityComboBox->insertItem(3, "阜阳");
    ui->arrCityComboBox->insertItem(4, "赣州");
    ui->arrCityComboBox->insertItem(5, "格尔木");
    ui->arrCityComboBox->insertItem(6, "固原");
    ui->arrCityComboBox->insertItem(7, "广元");
    ui->arrCityComboBox->insertItem(8, "广州");
    ui->arrCityComboBox->insertItem(9, "贵阳");
    ui->arrCityComboBox->insertItem(10, "桂林");
    ui->arrCityComboBox->insertItem(11, "哈尔滨");
    ui->arrCityComboBox->insertItem(12, "哈密");
    ui->arrCityComboBox->insertItem(13, "海口");
    ui->arrCityComboBox->insertItem(14, "海拉尔");
    ui->arrCityComboBox->insertItem(15, "邯郸");
    ui->arrCityComboBox->insertItem(16, "汉中");
    ui->arrCityComboBox->insertItem(17, "杭州");
    ui->arrCityComboBox->insertItem(18, "合肥");
    ui->arrCityComboBox->insertItem(19, "和田");
    ui->arrCityComboBox->insertItem(20, "黑河");
    ui->arrCityComboBox->insertItem(21, "呼和浩特");
    ui->arrCityComboBox->insertItem(22, "淮安");
    ui->arrCityComboBox->insertItem(23, "怀化");
    ui->arrCityComboBox->insertItem(24, "黄山");
    ui->arrCityComboBox->insertItem(25, "惠州");
    ui->arrCityComboBox->insertItem(26, "鸡西");
    ui->arrCityComboBox->insertItem(27, "济南");
    ui->arrCityComboBox->insertItem(28, "济宁");
    ui->arrCityComboBox->insertItem(29, "加格达奇");
    ui->arrCityComboBox->insertItem(30, "佳木斯");
    ui->arrCityComboBox->insertItem(31, "嘉峪关");
    ui->arrCityComboBox->insertItem(32, "揭阳");
    ui->arrCityComboBox->insertItem(33, "金昌");
    ui->arrCityComboBox->insertItem(34, "金门");
    ui->arrCityComboBox->insertItem(35, "锦州");
    ui->arrCityComboBox->insertItem(36, "嘉义");
    ui->arrCityComboBox->insertItem(37, "西双版纳");
    ui->arrCityComboBox->insertItem(38, "建三江");
    ui->arrCityComboBox->insertItem(39, "晋江");
    ui->arrCityComboBox->insertItem(40, "井冈山");
    ui->arrCityComboBox->insertItem(41, "景德镇");
    ui->arrCityComboBox->insertItem(42, "九江");
    ui->arrCityComboBox->insertItem(43, "九寨沟");
  } else if (arg1 == "KLMN") {
    ui->arrCityComboBox->insertItem(0, "喀什");
    ui->arrCityComboBox->insertItem(1, "凯里");
    ui->arrCityComboBox->insertItem(2, "康定");
    ui->arrCityComboBox->insertItem(3, "克拉玛依");
    ui->arrCityComboBox->insertItem(4, "库车");
    ui->arrCityComboBox->insertItem(5, "库尔勒");
    ui->arrCityComboBox->insertItem(6, "昆明");
    ui->arrCityComboBox->insertItem(7, "拉萨");
    ui->arrCityComboBox->insertItem(8, "兰州");
    ui->arrCityComboBox->insertItem(9, "黎平");
    ui->arrCityComboBox->insertItem(10, "丽江");
    ui->arrCityComboBox->insertItem(11, "荔波");
    ui->arrCityComboBox->insertItem(12, "连云港");
    ui->arrCityComboBox->insertItem(13, "六盘水");
    ui->arrCityComboBox->insertItem(14, "临汾");
    ui->arrCityComboBox->insertItem(15, "林芝");
    ui->arrCityComboBox->insertItem(16, "临沧");
    ui->arrCityComboBox->insertItem(17, "临沂");
    ui->arrCityComboBox->insertItem(18, "柳州");
    ui->arrCityComboBox->insertItem(19, "泸州");
    ui->arrCityComboBox->insertItem(20, "洛阳");
    ui->arrCityComboBox->insertItem(21, "吕梁");
    ui->arrCityComboBox->insertItem(22, "澜沧");
    ui->arrCityComboBox->insertItem(23, "龙岩");
    ui->arrCityComboBox->insertItem(24, "满洲里");
    ui->arrCityComboBox->insertItem(25, "芒市");
    ui->arrCityComboBox->insertItem(26, "梅州");
    ui->arrCityComboBox->insertItem(27, "绵阳");
    ui->arrCityComboBox->insertItem(28, "漠河");
    ui->arrCityComboBox->insertItem(29, "牡丹江");
    ui->arrCityComboBox->insertItem(30, "马祖");
    ui->arrCityComboBox->insertItem(31, "南昌");
    ui->arrCityComboBox->insertItem(32, "南充");
    ui->arrCityComboBox->insertItem(33, "南京");
    ui->arrCityComboBox->insertItem(34, "南宁");
    ui->arrCityComboBox->insertItem(35, "南通");
    ui->arrCityComboBox->insertItem(36, "南阳");
    ui->arrCityComboBox->insertItem(37, "宁波");
    ui->arrCityComboBox->insertItem(38, "宁蒗");
  } else if (arg1 == "OPQR") {
    ui->arrCityComboBox->insertItem(0, "攀枝花");
    ui->arrCityComboBox->insertItem(1, "普洱");
    ui->arrCityComboBox->insertItem(2, "齐齐哈尔");
    ui->arrCityComboBox->insertItem(3, "黔江");
    ui->arrCityComboBox->insertItem(4, "且末");
    ui->arrCityComboBox->insertItem(5, "秦皇岛");
    ui->arrCityComboBox->insertItem(6, "青岛");
    ui->arrCityComboBox->insertItem(7, "庆阳");
    ui->arrCityComboBox->insertItem(8, "衢州");
    ui->arrCityComboBox->insertItem(9, "日喀则");
    ui->arrCityComboBox->insertItem(10, "日照");
  } else if (arg1 == "STUV") {
    ui->arrCityComboBox->insertItem(0, "三亚");
    ui->arrCityComboBox->insertItem(1, "上海");
    ui->arrCityComboBox->insertItem(2, "深圳");
    ui->arrCityComboBox->insertItem(3, "神农架");
    ui->arrCityComboBox->insertItem(4, "沈阳");
    ui->arrCityComboBox->insertItem(5, "石家庄");
    ui->arrCityComboBox->insertItem(6, "塔城");
    ui->arrCityComboBox->insertItem(7, "台州");
    ui->arrCityComboBox->insertItem(8, "太原");
    ui->arrCityComboBox->insertItem(9, "扬州");
    ui->arrCityComboBox->insertItem(10, "唐山");
    ui->arrCityComboBox->insertItem(11, "腾冲");
    ui->arrCityComboBox->insertItem(12, "天津");
    ui->arrCityComboBox->insertItem(13, "天水");
    ui->arrCityComboBox->insertItem(14, "通辽");
    ui->arrCityComboBox->insertItem(15, "铜仁");
    ui->arrCityComboBox->insertItem(16, "吐鲁番");
  } else if (arg1 == "WXYZ") {
    ui->arrCityComboBox->insertItem(0, "万州");
    ui->arrCityComboBox->insertItem(1, "威海");
    ui->arrCityComboBox->insertItem(2, "潍坊");
    ui->arrCityComboBox->insertItem(3, "温州");
    ui->arrCityComboBox->insertItem(4, "文山");
    ui->arrCityComboBox->insertItem(5, "乌海");
    ui->arrCityComboBox->insertItem(6, "乌兰浩特");
    ui->arrCityComboBox->insertItem(7, "乌鲁木齐");
    ui->arrCityComboBox->insertItem(8, "无锡");
    ui->arrCityComboBox->insertItem(9, "梧州");
    ui->arrCityComboBox->insertItem(10, "武汉");
    ui->arrCityComboBox->insertItem(11, "武夷山");
    ui->arrCityComboBox->insertItem(12, "西安");
    ui->arrCityComboBox->insertItem(13, "西昌");
    ui->arrCityComboBox->insertItem(14, "西宁");
    ui->arrCityComboBox->insertItem(15, "锡林浩特");
    ui->arrCityComboBox->insertItem(16, "厦门");
    ui->arrCityComboBox->insertItem(17, "香格里拉");
    ui->arrCityComboBox->insertItem(18, "襄阳");
    ui->arrCityComboBox->insertItem(19, "兴义");
    ui->arrCityComboBox->insertItem(20, "徐州");
    ui->arrCityComboBox->insertItem(21, "香港");
    ui->arrCityComboBox->insertItem(22, "烟台");
    ui->arrCityComboBox->insertItem(23, "延安");
    ui->arrCityComboBox->insertItem(24, "延吉");
    ui->arrCityComboBox->insertItem(25, "盐城");
    ui->arrCityComboBox->insertItem(26, "伊春");
    ui->arrCityComboBox->insertItem(27, "伊宁");
    ui->arrCityComboBox->insertItem(28, "宜宾");
    ui->arrCityComboBox->insertItem(29, "宜昌");
    ui->arrCityComboBox->insertItem(30, "宜春");
    ui->arrCityComboBox->insertItem(31, "义乌");
    ui->arrCityComboBox->insertItem(32, "银川");
    ui->arrCityComboBox->insertItem(33, "永州");
    ui->arrCityComboBox->insertItem(34, "榆林");
    ui->arrCityComboBox->insertItem(35, "玉树");
    ui->arrCityComboBox->insertItem(36, "运城");
    ui->arrCityComboBox->insertItem(37, "湛江");
    ui->arrCityComboBox->insertItem(38, "张家界");
    ui->arrCityComboBox->insertItem(39, "张家口");
    ui->arrCityComboBox->insertItem(40, "张掖");
    ui->arrCityComboBox->insertItem(41, "昭通");
    ui->arrCityComboBox->insertItem(42, "郑州");
    ui->arrCityComboBox->insertItem(43, "中卫");
    ui->arrCityComboBox->insertItem(44, "舟山");
    ui->arrCityComboBox->insertItem(45, "珠海");
    ui->arrCityComboBox->insertItem(46, "遵义");
  }
}

void UserWindow::on_orderPaymentPushButton_clicked() {
  QList<int> payList;

  for (int i = 0; i < ui->orderCenterTableWidget->rowCount(); ++i) {
    if (ui->orderCenterTableWidget->item(i, 0)->checkState()) {
      payList << i;
    }
  }

  if (payList.isEmpty()) {
    infoWindow("请选择要支付的订单!");
    return;
  }

  if (questionWindow("确定支付该订单吗?") == QMessageBox::No) {
    infoWindow("您已取消订单支付!");
    orderCenterShow();
    return;
  }

  for (int i = 0; i < payList.size(); ++i) {
    orderNum = ui->orderCenterTableWidget->item(payList.at(i), 1)->text();

    QSqlTableModel orderInfoModel;
    orderInfoModel.setTable("order_info");
    orderInfoModel.setFilter(tr("order_num = '%1'").arg(orderNum));
    orderInfoModel.select();

    if (orderInfoModel.rowCount() == 1) {
      orderPayState =
          orderInfoModel.data(orderInfoModel.index(0, 4)).toString();
      if (orderPayState == "未支付") {
        QDateTime localDateTime(QDateTime::currentDateTime());
        orderPayTime = localDateTime.toString("hh:mm:ss");

        QString localDate = localDateTime.toString("yyyyMMdd");
        QString eleTime = localDateTime.toString("hhmmss");

        orderPayState = "已支付";
        eleTicketNum =
            ui->orderCenterTableWidget->item(payList.at(i), 2)->text() +
            localDate + eleTime;
        eleOrderNum =
            ui->orderCenterTableWidget->item(payList.at(i), 1)->text();
        eleTicketUserName =
            ui->orderCenterTableWidget->item(payList.at(i), 4)->text();
        eleFlightNum =
            ui->orderCenterTableWidget->item(payList.at(i), 2)->text();
        eleFlightDepCity =
            ui->orderCenterTableWidget->item(payList.at(i), 8)->text();
        eleFlightArrCity =
            ui->orderCenterTableWidget->item(payList.at(i), 9)->text();
        eleFlightDate =
            ui->orderCenterTableWidget->item(payList.at(i), 6)->text();
        eleFlightTime =
            ui->orderCenterTableWidget->item(payList.at(i), 7)->text();
        eleFlightPrice =
            ui->orderCenterTableWidget->item(payList.at(i), 10)->text();

        QString payInfo = tr("UPDATE order_info SET order_pay_state = '%1'"
                             "order_pay_time = '%2' WHERE order_num = '%3'")
                              .arg(orderPayState, orderPayTime, orderNum);

        QString eleInfo =
            tr("INSERT INTO ele_ticket"
               "(e_ticket_num, e_order_num, e_ticket_u_name, e_flight_num,"
               "e_filght_dep_city, e_flight_arr_city, e_flight_date, "
               "e_flight_dep_time,"
               "e_flight_price)"
               "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')")
                .arg(eleTicketNum, eleOrderNum, eleTicketUserName, eleFlightNum,
                     eleFlightDepCity, eleFlightArrCity, eleFlightDate,
                     eleFlightTime, eleFlightPrice);

        QSqlQuery payQuery;
        QSqlQuery eleQuery;

        if (payQuery.exec(payInfo) && eleQuery.exec(eleInfo)) {
          infoWindow(tr("您的订单 %1 支付成功!").arg(eleOrderNum));
        } else {
          infoWindow("支付失败!");
        }
      } else {
        infoWindow(tr("您的订单号 %1 已支付!").arg(eleOrderNum));
      }
      orderCenterShow();
    }
  }
}

void UserWindow::on_cancelButtonPushButton_clicked() {
  QList<int> cancelList;

  for (int i = 0; i < ui->orderCenterTableWidget->rowCount(); ++i) {
    if (ui->orderCenterTableWidget->item(i, 0)->checkState()) {
      cancelList << i;
    }
  }

  if (cancelList.isEmpty()) {
    infoWindow("请选择需要退订的订单!");
    return;
  }

  if (questionWindow("确定退订该订单吗?") == QMessageBox::No) {
    infoWindow("您已取消退订订单!");
    orderCenterShow();
    return;
  }

  for (int i = 0; i < cancelList.size(); ++i) {
    orderNum = ui->orderCenterTableWidget->item(cancelList.at(i), 1)->text();

    QSqlTableModel orderInfoModel;
    orderInfoModel.setTable("order_info");
    orderInfoModel.setFilter(tr("order_num = '%1'").arg(orderNum));
    orderInfoModel.select();

    if (orderInfoModel.rowCount() == 1) {
      orderPayState =
          orderInfoModel.data(orderInfoModel.index(0, 4)).toString();
      if (orderPayState == "已支付") {
        orderPayState = "未支付";
        orderPayTime = "";

        auto cancelInfo = tr("UPDATE order_info SET order_pay_state = '%1'"
                             "order_pay_time = '%2' WHERE order_num = '%3'")
                              .arg(orderPayState, orderPayTime, orderNum);

        auto eleInfo =
            tr("DELETE FROM ele_ticket WHERE e_order_num = '%1'").arg(orderNum);

        QSqlQuery cancelQuery;
        QSqlQuery eleQuery;

        if (cancelQuery.exec(cancelInfo) && eleQuery.exec(eleInfo)) {
          infoWindow(tr("您的订单 %1 退订成功!").arg(orderNum));
        } else {
          infoWindow("退订失败!");
        }
      } else {
        infoWindow(tr("您的订单号 %1 未支付!").arg(orderNum));
      }
      orderCenterShow();
    }
  }
}

void UserWindow::on_deleteOrderPushButton_clicked() {
  QList<int> deleteList;

  for (int i = 0; i < ui->orderCenterTableWidget->rowCount(); ++i) {
    if (ui->orderCenterTableWidget->item(i, 0)->checkState()) {
      deleteList << i;
    }
  }

  if (deleteList.isEmpty()) {
    infoWindow("请选择需要删除的订单!");
    return;
  }

  if (questionWindow("确定删除该订单吗?") == QMessageBox::No) {
    infoWindow("您已取消删除订单!");
    orderCenterShow();
    return;
  }

  for (int i = 0; i < deleteList.size(); ++i) {
    orderNum = ui->orderCenterTableWidget->item(deleteList.at(i), 1)->text();

    QSqlTableModel orderInfoModel;
    orderInfoModel.setTable("order_info");
    orderInfoModel.setFilter(tr("order_num = '%1'").arg(orderNum));
    orderInfoModel.select();

    if (orderInfoModel.rowCount() == 1) {
      orderPayState =
          orderInfoModel.data(orderInfoModel.index(0, 4)).toString();

      if (orderPayState == "未支付") {
        QSqlQuery deleteQuery;
        QString deleteInfo =
            tr("DELETE FROM order_info WHERE order_num = '%1'").arg(orderNum);

        if (deleteQuery.exec(deleteInfo)) {
          infoWindow(tr("您的订单 %1 删除成功!").arg(orderNum));
        } else {
          infoWindow("删除失败!");
        }
      } else {
        infoWindow(
            tr("您的订单号 %1 已支付, 无法删除, 请先退订订单").arg(orderNum));
      }
      orderCenterShow();
    }
  }
}

void UserWindow::infoWindow(const QString &info) {
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

int UserWindow::questionWindow(const QString &question) {
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
