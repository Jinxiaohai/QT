#ifndef DONEWDIALOG_H
#define DONEWDIALOG_H

#include <QDialog>

namespace Ui {
  class DoNewDialog;
}

class DoNewDialog : public QDialog {
  Q_OBJECT
public:
  DoNewDialog(QWidget *parent = 0);
  ~DoNewDialog();
  int getWidth();   
  int getHeight();  
  QColor getBackColor();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::DoNewDialog *ui;
  QColor backColor;  

private slots:
  void on_toolButton_clicked();
};

#endif // DONEWDIALOG_H
