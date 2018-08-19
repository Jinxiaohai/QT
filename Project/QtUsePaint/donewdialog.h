#ifndef DONEWDIALOG_H
#define DONEWDIALOG_H

#include <QDialog>

namespace Ui {
class DoNewDialog;
}

class DoNewDialog : public QDialog {
  Q_OBJECT

 public:
  explicit DoNewDialog(QWidget *parent = 0);
  ~DoNewDialog();

  int getWidth() const;
  int getHeight() const;
  QColor getBackColor();

 protected:
  void changeEvent(QEvent *e);

 private slots:
  void on_toolButton_clicked();

 private:
  Ui::DoNewDialog *ui;

  QColor backColor;
};

#endif  // DONEWDIALOG_H
