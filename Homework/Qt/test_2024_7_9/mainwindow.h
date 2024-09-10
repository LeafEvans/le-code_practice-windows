#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "user.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    User *curUser;


public slots:
    void recUser(User *user);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
