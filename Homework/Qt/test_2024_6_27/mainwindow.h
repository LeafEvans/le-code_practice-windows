#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QAbstractButton>
#include <QFileDialog>
#include <QCloseEvent>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QBoxLayout>

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

    // 新建文件
    void newFile();
    // 判断是否需要保存
    bool maybeSave();
    // 保存操作
    bool save();
    // 另存为操作
    bool saveAs();
    // 保存文件操作
    bool saveFile(const QString &fileName);
    // 加载文件操作
    bool loadFile(const QString &fileName);
    // 关闭事件操作
    void closeEvent(QCloseEvent *event);



private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionClose_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionExit_triggered();

    void on_actionCancel_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void showFindText();

    void on_actionfind_triggered();

private:
    Ui::MainWindow *ui;

    // 真：文件未保存
    // 假：文件已保存
    bool isUnSaved;

    // 保存当前文件路径
    QString curFilePath;

    // 可编辑行对象
    QLineEdit *findLineEdit;

    // 对话框对象
    QDialog *findDlg;

};
#endif // MAINWINDOW_H
