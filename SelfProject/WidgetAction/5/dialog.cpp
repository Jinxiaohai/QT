#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);

  QRegExp regExp("[A-Za-z][1-9][1-9]{0,2}");
  ui->lineEdit->setValidator(new QRegExpValidator(regExp, this));
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

void Dialog::on_lineEdit_textChanged() {
  ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());
}
