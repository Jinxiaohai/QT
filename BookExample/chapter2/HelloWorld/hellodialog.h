#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#if QT_VERSION >= 0x050000
#include <QDialog>
#else
#include <QDialog>
#endif

namespace Ui {
class HelloDialog;
}

class HelloDialog : public QDialog {
  Q_OBJECT

 public:
  explicit HelloDialog(QWidget *parent = 0);
  ~HelloDialog();

 protected:
  void changeEvent(QEvent *e);

 private:
  Ui::HelloDialog *ui;
};

#endif  // HELLODIALOG_H
