#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  initUI();
  initConnections();
  setWindowTitle(tr("文本编辑器"));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initUI() {
  // 设置字体大小控件
  spinFontSize = new QSpinBox();
  spinFontSize->setMinimum(5);   // 最小值 5
  spinFontSize->setMaximum(50);  // 最大值 50
  ui->toolBar->addWidget(new QLabel(tr("字体大小:")));
  ui->toolBar->addWidget(spinFontSize);

  // 设置字体样式控件
  comboFont = new QFontComboBox();
  ui->toolBar->addWidget(new QLabel(tr("字体:")));
  ui->toolBar->addWidget(comboFont);
}

void MainWindow::on_actionBold_triggered(bool checked) {
  QTextCharFormat fmt;               // 文本字体格式
  if (checked) {                     // 检查
    fmt.setFontWeight(QFont::Bold);  // 如果按下粗体按钮，则设置字体为粗体
  } else {
    fmt.setFontWeight(QFont::Normal);  // 没有就设置为正常
  }
  ui->plainTextEdit->mergeCurrentCharFormat(fmt);  // 融合原本字体样式
}

void MainWindow::on_actionItalic_triggered(bool checked) {
  QTextCharFormat fmt;
  fmt.setFontItalic(checked);                      // 设置斜体
  ui->plainTextEdit->mergeCurrentCharFormat(fmt);  // 融合原本字体样式
}

void MainWindow::on_actionUnderscore_triggered(bool checked) {
  QTextCharFormat fmt;
  fmt.setFontUnderline(checked);
  ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::initConnections() {
  // 连接字体 spinBox
  connect(spinFontSize, SIGNAL(valueChanged(int)), this,
          SLOT(on_spinFontSize_valueChanged(int)));
  // 连接字体 comboBox
  connect(comboFont, SIGNAL(currentIndexChanged(QString)), this,
          SLOT(on_comboFont_currentIndexChanged(QString)));
}

// 设置字体大小的槽函数
void MainWindow::on_spinFontSize_valueChanged(int aFontSize) {
  QTextCharFormat fmt;
  fmt.setFontPointSize(aFontSize);  // 字体大小
  ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

// 设置特定字体的槽函数
void MainWindow::on_comboFont_currentIndexChanged(const QString &text) {
  QTextCharFormat fmt;
  fmt.setFontFamilies({text});
  ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

// 设置颜色的槽函数
void MainWindow::on_actionColor_triggered() {
  QPalette pal = ui->plainTextEdit->palette();  // 获取一个调色板
  QColor iniColor = pal.color(QPalette::Text);  // 从调色板中获取当前文本信息
  // 弹出对话框来获取颜色
  // initial: 默认颜色
  // parent: 父窗口
  // title: 窗口标题
  QColor color = QColorDialog::getColor(iniColor, this, tr("选择颜色"));

  // 检查颜色是否有效
  if (!color.isValid()) {
    return;
  }

  QTextCharFormat fmt;
  fmt.setForeground(color);
  ui->plainTextEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionOpen_triggered() {
  QString curPath = QDir::currentPath();  // 当前文件路径
  QString filter = "文本文件(*.txt)";  // 限制对话框只显示文本文件
  QString fileName = QFileDialog::getOpenFileName(this,  // 父窗口
                                                  tr("打开文本文件"),  // 标题
                                                  curPath,  // 当前路径
                                                  filter);  // 过滤器

  // 空的就代表直接关闭对话框
  if (fileName.isEmpty()) {
    return;
  }

  // 当前文件名
  QString curFileName = "当前文件: " + fileName;
  // 更新 label 名
  ui->label->setText(curFileName);

  QFile file(fileName);  // 创建一个 QFile 对象，代表选择的文件
  if (file.open(QIODevice::ReadWrite)) {  // 按照读入写入模式打开文件
    ui->plainTextEdit->setPlainText(file.readAll());  // 将文本文件的内容
    file.close();                                     // 关闭文件
  }
}

void MainWindow::on_actionSave_triggered() {
  QString curPath = QDir::currentPath();
  QString filter = "文本文件(*.txt)";
  QString fileName =
      QFileDialog::getSaveFileName(this, "另存为", curPath, filter);

  if (fileName.isEmpty()) {
    return;
  }

  QFile file(fileName);

  if (file.open(QIODevice::WriteOnly)) {
    QString content = ui->plainTextEdit->toPlainText();
    QByteArray strBytes = content.toUtf8();
    file.write(strBytes, strBytes.length());
  }
}
