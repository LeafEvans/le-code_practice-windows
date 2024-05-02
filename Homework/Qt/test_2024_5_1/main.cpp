#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class CustomWidget : public QWidget {
 public:
  explicit CustomWidget(QWidget *parent = nullptr) : QWidget(parent) {}

 protected:
  void mousePressEvent(QMouseEvent *event) override {
    if (event->button() == Qt::LeftButton) {
      m_clickedPoint = event->pos();
      update();
    }
  }

  void paintEvent(QPaintEvent *event) override {
    QPainter painter(this);
    painter.setPen(Qt::darkRed);
    painter.setBrush(Qt::blue);
    painter.drawRect(50, 50, 200, 100);

    painter.setBrush(Qt::red);
    painter.drawEllipse(m_clickedPoint, 20, 20);
  }

 private:
  QPoint m_clickedPoint;
};


int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  CustomWidget widget;
  widget.setWindowTitle("Qt 示例程序");
  widget.resize(400, 300);
  widget.show();

  return QApplication::exec();
}
