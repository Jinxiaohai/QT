#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
}

Dialog::~Dialog() { delete ui; }

void Dialog::displayCheckBox() {
  QString str;
  str = "";
  if (ui->checkBox->isChecked()) {
    str += "checkBox1 is Checked";
  }
  if (ui->checkBox_2->isChecked()) {
    str += "checkBox2 is Checked";
  }
  if (ui->checkBox_3->isChecked()) {
    str += "checkBox3 is Checked";
  }

  ui->label_2->setText(str);
}

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

void Dialog::on_checkBox_3_clicked() {
  if (ui->checkBox_3->isChecked()) {
    this->displayCheckBox();
  } else {
    this->displayCheckBox();
  }
}

void Dialog::on_checkBox_2_clicked() {
  if (ui->checkBox_2->isChecked()) {
    this->displayCheckBox();
  } else {
    this->displayCheckBox();
  }
}

void Dialog::on_checkBox_clicked() {
  if (ui->checkBox->isChecked()) {
    this->displayCheckBox();
  } else {
    this->displayCheckBox();
  }
}

void Dialog::on_radioButton_3_clicked() {
  ui->radioButton_3->setChecked(true);
  ui->label->setText(tr("RadioButton3 is Checked!"));
}

void Dialog::on_radioButton_2_clicked() {
  ui->radioButton_2->setChecked(true);
  ui->label->setText(tr("Radio Button2 is Checked"));
}

void Dialog::on_radioButton_clicked() {
  ui->radioButton->setChecked(true);
  ui->label->setText(tr("RadioButton1 is Checked"));
}

void Dialog::on_btn_CheckBox_clicked() {
  QString str;
  str = "";
  ui->label_2->adjustSize();
  if (ui->checkBox->isChecked()) {
    str += "checkBox1 is Checked;";
  }
  if (ui->checkBox_2->isChecked()) {
    str += "checkBox2 is Checked;";
  }
  if (ui->checkBox_3->isChecked()) {
    str += "checkBox3 is Checked;";
  }
  ui->label_2->setText(str);
}

void Dialog::on_btn_RadioButton_clicked() {
  ui->radioButton->setChecked(true);
  ui->label->setText(tr("RadioButton1 is Checked"));
}
