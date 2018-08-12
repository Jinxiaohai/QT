#include <QMessageBox>

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);

  //  ui->comboBox->addItem("Hello");
  //  ui->comboBox->addItem("World");

  for (int i = 0; i != 9; ++i) {
    ui->comboBox->addItem(QString::number(i) + " item");
  }
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
  QMessageBox::information(this, "Title", ui->comboBox->currentText());
}
