#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *btn = new QPushButton(this);  // 创建一个按钮对象
    QLineEdit *edit = new QLineEdit(this);     // 创建一个行编辑器对象

    QGridLayout *layout = new QGridLayout;     // 创建一个网格对象

    layout->addWidget(btn, 0, 0, 1, 1);        // 添加部件
    layout->addWidget(edit, 0, 1, 1, 2);

    layout->addWidget(ui->textEdit, 1, 0, 1, 3);

    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
