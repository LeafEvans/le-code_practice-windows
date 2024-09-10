#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    isUnSaved = true;

    curFilePath = tr("未保存文件.txt");

    setWindowTitle(curFilePath);
}

void MainWindow::newFile() {
    if (maybeSave()) {
        isUnSaved = true;
        curFilePath = tr("未保存文件");
        setWindowTitle(curFilePath);

        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave() {
    if (ui->textEdit->document()->isModified()) {
        QMessageBox box;
        box.setWindowTitle(tr("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFilePath + tr("尚未保存, 是否保存？"));

        box.addButton(tr("是(&Y)"), QMessageBox::YesRole);
        box.addButton(tr("否(&N)"), QMessageBox::NoRole);
        box.addButton(tr("取消"), QMessageBox::RejectRole);

        box.exec();

        QMessageBox::StandardButton clickedBtn = box.standardButton(box.clickedButton());

        if (clickedBtn == QMessageBox::Yes) {
            return save();
        } else if (clickedBtn == QMessageBox::No){
            return false;
        }
    }

    return true;
}

bool MainWindow::save() {
    if (isUnSaved) {
        return saveAs();
    } else {
        return saveFile(curFilePath);
    }
}

bool MainWindow::saveAs() {
    QString fileName = QFileDialog::
        getSaveFileName(this,
                        tr("另存为"),
                        curFilePath);

    if (fileName.isEmpty()) {
        return false;
    }

    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName) {
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法写入文件 %1:\n%2")
                                 .arg(fileName, file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    out << ui->textEdit->toPlainText();

    QApplication::restoreOverrideCursor();

    isUnSaved = false;

    curFilePath = QFileInfo(fileName).canonicalFilePath();

    setWindowTitle(curFilePath);

    return true;
}

bool MainWindow::loadFile(const QString &fileName) {
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("多文本编辑器"),
                             tr("无法读取文件 %1:\n%2")
                                 .arg(fileName, file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());

    QApplication::restoreOverrideCursor();

    curFilePath = QFileInfo(fileName).canonicalFilePath();

    setWindowTitle(curFilePath);

    return true;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered() {
    newFile();
}




void MainWindow::on_actionOpen_triggered() {
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);

        if (!fileName.isEmpty()) {
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}



void MainWindow::on_actionClose_triggered() {
    if (maybeSave()) {
        ui->textEdit->setVisible(false);
    }
}




void MainWindow::on_actionSave_triggered() {
    save();
}


void MainWindow::on_actionSaveAs_triggered() {
    saveAs();
}


void MainWindow::on_actionExit_triggered() {
    on_actionClose_triggered();
    qApp->quit();
}


void MainWindow::on_actionCancel_triggered() {
    ui->textEdit->undo();
}




void MainWindow::on_actionCut_triggered() {
    ui->textEdit->cut();
}




void MainWindow::on_actionCopy_triggered() {
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered() {
    ui->textEdit->paste();
}

