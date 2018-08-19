#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

 public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();

  void displayCheckBox();

 protected:
  void changeEvent(QEvent *e);

 private slots:
  void on_checkBox_3_clicked();

  void on_checkBox_2_clicked();

  void on_checkBox_clicked();

  void on_radioButton_3_clicked();

  void on_radioButton_2_clicked();

  void on_radioButton_clicked();

  void on_btn_CheckBox_clicked();

  void on_btn_RadioButton_clicked();

 private:
  Ui::Dialog *ui;
};

#endif  // DIALOG_H
