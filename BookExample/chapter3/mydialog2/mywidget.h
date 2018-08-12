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

 private
slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

 private:
  Ui::MyWidget *ui;
};

#endif  // MYWIDGET_H
