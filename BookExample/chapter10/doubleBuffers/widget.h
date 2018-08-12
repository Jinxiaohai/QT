#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

 protected:
  void changeEvent(QEvent *e);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void paintEvent(QPaintEvent *event);

 private:
  Ui::Widget *ui;
  QPixmap pix;
  QPixmap tempPix;
  QPoint startPoint;
  QPoint endPoint;
  bool isDrawing;
};

#endif  // WIDGET_H
