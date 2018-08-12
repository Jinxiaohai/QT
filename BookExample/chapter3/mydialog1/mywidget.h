#ifndef MYWIDGET_H
#define MYWIDGET_H

#if QT_VERSION >= 0x050000
#include <QWidget>
#else
#include <QWidget>
#endif

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget {
  Q_OBJECT

 public:
  explicit MyWidget(QWidget *parent = 0);
  ~MyWidget();

 protected:
  void changeEvent(QEvent *e);

 public
slots:
  void showChildDialog();

 private:
  Ui::MyWidget *ui;
};

#endif  // MYWIDGET_H
