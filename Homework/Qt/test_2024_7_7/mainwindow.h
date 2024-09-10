#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QFontComboBox>
#include <QLabel>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_actionBold_triggered(bool checked);

    void on_actionItalic_triggered(bool checked);

    void on_actionUnderscore_triggered(bool checked);

    void on_spinFontSize_valueChanged(int);

    void on_comboFont_currentIndexChanged(const QString &);



    void on_actionColor_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QSpinBox *spinFontSize;
    QFontComboBox *comboFont;
    QLabel *currentFile;

    void initUI();
    void initConnections();
};
#endif // MAINWINDOW_H
