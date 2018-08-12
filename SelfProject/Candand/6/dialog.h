#ifndef DIALOG_H
#define DIALOG_H

#include <QtGlobal>


#include <QDialog>


namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();

protected:
  void changeEvent(QEvent *e);

private slots:
  void on_pushButton_clicked();

private:
  Ui::Dialog *ui;
};

#endif // DIALOG_H
