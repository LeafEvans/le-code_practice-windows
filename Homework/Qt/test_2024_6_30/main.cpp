#include <QApplication>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  auto infoLabel = new QLabel;
  auto openLabel = new QLabel;
  auto cmdLineEdit = new QLineEdit;
  auto commitButton = new QPushButton;
  auto cancelButton = new QPushButton;
  auto browseButton = new QPushButton;

  infoLabel->setText("input cmd:");
  openLabel->setText("打开");
  commitButton->setText("commit");
  cancelButton->setText("cancel");
  browseButton->setText("...");

  auto cmdLayout = new QHBoxLayout;
  cmdLayout->addWidget(openLabel);
  cmdLayout->addWidget(cmdLineEdit);

  auto buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(commitButton);
  buttonLayout->addWidget(cancelButton);
  buttonLayout->addWidget(browseButton);

  auto mainLayout = new QVBoxLayout;
  mainLayout->addWidget(infoLabel);
  mainLayout->addLayout(cmdLayout);
  mainLayout->addLayout(buttonLayout);

  QWidget w;
  w.setLayout(mainLayout);
  w.setWindowTitle("Man");
  w.show();

  return QApplication::exec();
}