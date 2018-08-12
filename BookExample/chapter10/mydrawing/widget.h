#ifndef WIDGET_H
#define WIDGET_H

#if QT_VERSION >= 0x050000
#include <QWidget>
#else
#include <QWidget>
#endif

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
  void paintEvent(QPaintEvent *event);

 private:
  Ui::Widget *ui;
};

#endif  // WIDGET_H
