#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>

class QLineEdit;
class QDialog;

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

    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);
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

private:
    Ui::MainWindow *ui;

    bool isUnSaved;

    QString curFilePath;
};
#endif // MAINWINDOW_H
