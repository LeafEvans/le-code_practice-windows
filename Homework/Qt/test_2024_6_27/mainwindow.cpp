#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  isUnSaved = true;  // 初始化，未保存状态

  curFilePath = tr("未命名文件.txt");  // 设置一个默认的当前文件名称

  setWindowTitle(curFilePath);  // 设置窗口标题

  findDlg = new QDialog(this);
  findDlg->setWindowTitle(tr("查找"));
  findLineEdit = new QLineEdit(findDlg);

  QPushButton *btn = new QPushButton(tr("查找下一个"), findDlg);
  QVBoxLayout *layout = new QVBoxLayout(findDlg);

  layout->addWidget(findLineEdit);
  layout->addWidget(btn);

  connect(btn, &QPushButton::clicked, this, &MainWindow::showFindText);
}

// 新建文件
void MainWindow::newFile() {
  // 如果文档更改
  // 使用 maybeSave() 判断是否需要保存
  // 如果保存完毕，则新建文档，进行初始化
  if (maybeSave()) {
    isUnSaved = true;                    // 代表此时新建的文件为保存
    curFilePath = tr("未命名文件.txt");  // 当前文件路径
    setWindowTitle(curFilePath);  // 设置窗口标题为当前文件路径

    ui->textEdit->clear();  // 清除编辑区域

    ui->textEdit->setVisible(true);  // 设置编辑区域可见
  }
}

// 判断是否需要保存
// 弹出一个窗口询问用户是否保存
bool MainWindow::maybeSave() {
  // 如果文档更改
  if (ui->textEdit->document()->isModified()) {
    QMessageBox box;                                       // 设置信息窗口
    box.setWindowTitle(tr("警告"));                        // 警告窗口标题
    box.setIcon(QMessageBox::Warning);                     // 设置窗口图标
    box.setText(curFilePath + tr("尚未保存，是否保存?"));  // 设置窗口文本

    // 添加标准按钮
    box.addButton(
        tr("是(&Y)"),
        QMessageBox::YesRole);  // YesRole 是枚举值，类型为 StandardButton
    box.addButton(tr("否(&N)"), QMessageBox::NoRole);
    box.addButton(tr("取消"), QMessageBox::RejectRole);

    // 显示对话框并等待用户选择
    box.exec();

    // 获取用户点击的标准按钮类型
    // 将点击按钮的 QAbstractButton 类型的返回值转化为 StandardButton 的返回值
    QMessageBox::StandardButton clickedBtn =
        box.standardButton(box.clickedButton());

    // 根据按钮类型进行处理
    // 进行比较
    if (clickedBtn == QMessageBox::Yes) {
      // 如果点击是，便保存
      return save();
    } else if (clickedBtn == QMessageBox::No) {
      // 点击不是，便返回 false
      // 代表未保存
      return false;
    }
  }

  // 如果文档没有更改，返回 true
  // 不执行弹出信息对话框操作
  // 文档没有变化就说明保存了
  return true;
}

// 保存文件操作
bool MainWindow::save() {
  // 判断是否保存
  if (isUnSaved) {    // 如果未保存
    return saveAs();  // 是便执行 SaveAs 操作
  } else {
    // 如果已经保存过了，就按照当前文件路径来保存
    return saveFile(curFilePath);  // 否则就按照当前文件名保存文件
  }
}

// 另存为文件操作
bool MainWindow::saveAs() {
  // 定义一个文件名
  // getSaveFileName 弹出文件返回对话框并且返回用户选择的文件路径和文件名
  // this 指的是当前的父窗口，将对话框绑定到父窗口上
  // ”另存为“ 是对话框的名称
  // curFileName 是默认的文件路径和文件名
  QString fileName =
      QFileDialog::getSaveFileName(this, tr("另存为"), curFilePath);

  // 如果文件名为空
  if (fileName.isEmpty()) {
    // 返回 false
    // 代表保存失败
    return false;
  }

  // 否则返回按照文件路径保存文件
  return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName) {
  QFile file(fileName);  // 新建一个 QFile 对象，表示文件

  // 以只写模式或者文本模式打开文件失败
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    // 弹出警告框，第一个文本为标题，第二个文本为显示信息
    // %1 和 %2 分别会被 fileName 和 file.errorString() 取代
    QMessageBox::warning(
        this, tr("多文档编辑器"),
        tr("无法写入文件 %1:\n%2").arg(fileName, file.errorString()));

    return false;  // 打开文件失败，返回 false
  }

  QTextStream out(
      &file);  // 使用文件对象创建一个 QTextStream 对象，用于写入文本

  // 设置鼠标光标为等待状态（通常是一个旋转的圈）
  QApplication::setOverrideCursor(Qt::WaitCursor);

  out << ui->textEdit->toPlainText();  // 将 textEdit 的纯文本内容写入到文件中

  // 重置鼠标光标为默认状态
  QApplication::restoreOverrideCursor();

  isUnSaved = false;  // 标记文档为已保存状态

  // 创建一个 QFileInfo 对象，并获取它的绝对路径
  curFilePath = QFileInfo(fileName).canonicalFilePath();

  // 将窗口标题设置为文件的绝对路径
  setWindowTitle(curFilePath);

  return true;  // 保存成功，返回 true
}

// 加载文件函数
bool MainWindow::loadFile(const QString &fileName) {
  QFile file(fileName);
  // 以只写模式或文本编辑模式打开失败
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(
        this, tr("多文本编辑器"),
        tr("无法读取文件%1:\n%2").arg(fileName, file.errorString()));

    return false;
  }

  QTextStream in(&file);  // 输入状态
  QApplication::setOverrideCursor(Qt::WaitCursor);
  // 将 ui 中的内容读取到文本编辑器中
  // in.readAll 是一个成员函数，读取文件流中的内容，转化为 QString
  // setPlainText 设置文本编辑器的内容
  ui->textEdit->setPlainText(in.readAll());

  QApplication::restoreOverrideCursor();  // 重置光标

  curFilePath = QFileInfo(fileName).canonicalFilePath();

  setWindowTitle(curFilePath);  // 设置窗口标题

  return true;
}

void MainWindow::closeEvent(QCloseEvent *event) {
  // 调用 maybeSave()
  // 判断是否需要保存
  if (maybeSave()) {
    // 允许关闭窗口
    event->accept();
  } else {
    // 阻止关闭窗口
    event->ignore();
  }
}

MainWindow::~MainWindow() { delete ui; }

// 新建文件槽函数
void MainWindow::on_actionNew_triggered() {
  // 创建一个新文件
  newFile();
}

// 打开文件槽函数
void MainWindow::on_actionOpen_triggered() {
  // 判断文件是否需要保存，并且进行保存操作
  if (maybeSave()) {
    // 文件名
    // 弹出一个文件对话框，得到打开文件的名字
    QString fileName = QFileDialog::getOpenFileName(this);
    // 如果文件名不是空的
    if (!fileName.isEmpty()) {
      // 加载文件
      loadFile(fileName);
      // 设置可见
      ui->textEdit->setVisible(true);
    }
  }
}

// 关闭编辑框的槽函数
void MainWindow::on_actionClose_triggered() {
  if (maybeSave()) {
    // 关闭文本框
    ui->textEdit->setVisible(false);
  }
}

// 保存文件
void MainWindow::on_actionSave_triggered() { save(); }

// 另存为操作
void MainWindow::on_actionSaveAs_triggered() { saveAs(); }

// 退出操作
void MainWindow::on_actionExit_triggered() {
  // 先执行关闭操作
  // 然后退出程序
  on_actionClose_triggered();
  qApp->quit();
}

// 撤销操作
void MainWindow::on_actionCancel_triggered() {
  // undo 会撤销最后一个编辑操作
  ui->textEdit->undo();
}

// 剪切操作
void MainWindow::on_actionCut_triggered() { ui->textEdit->cut(); }

// 复制操作
void MainWindow::on_actionCopy_triggered() { ui->textEdit->copy(); }

// 粘贴操作
void MainWindow::on_actionPaste_triggered() { ui->textEdit->paste(); }

void MainWindow::showFindText() {
  QString str = findLineEdit->text();

  bool ret = ui->textEdit->find(str, QTextDocument::FindBackward);

  if (!ret) {
    QMessageBox::warning(this, tr("查找"), tr("找不到%1").arg(str));
  }
}

void MainWindow::on_actionfind_triggered() { findDlg->show(); }
