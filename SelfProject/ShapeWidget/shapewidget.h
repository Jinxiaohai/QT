#ifndef SHAPEWIDGET_H
#define SHAPEWIDGET_H

#include <QMainWindow>
#include <QPoint>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QPaintEvent;
QT_END_NAMESPACE

class ShapeWidget : public QMainWindow {
  Q_OBJECT

 public:
  ShapeWidget(QWidget *parent = 0);
  ~ShapeWidget();

 protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void paintEvent(QPaintEvent *event);

 private:
  QPoint dragPosition;
};

#endif  // SHAPEWIDGET_H
