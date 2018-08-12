#include <QMessageBox>

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
}

Dialog::~Dialog() { delete ui; }

void Dialog::changeEvent(QEvent *e) {
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void Dialog::on_pushButton_clicked() {
  if (ui->radioButton1->isChecked()) {
    QMessageBox::information(this, "Title", ui->radioButton1->text());
  } else {
    QMessageBox::information(this, "Title", ui->radioButton2->text());
  }
}
