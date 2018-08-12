#ifndef MYDIALOG_H
#define MYDIALOG_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog {
  Q_OBJECT

 public:
  explicit MyDialog(QWidget *parent = 0);
  ~MyDialog();

 protected:
  void changeEvent(QEvent *e);

 private
slots:
  void on_pushButton_clicked();

 private:
  Ui::MyDialog *ui;
};

#endif  // MYDIALOG_H
