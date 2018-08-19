#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent) {
  this->setMinimumSize(265, 190);
  this->resize(365, 240);
  int w = width() - minimumWidth();

  QLabel *nameLabel = new QLabel(tr("Name:"), this);
  QLabel *pwLabel = new QLabel(tr("Passwd:"), this);
  QLineEdit *nameLineEdit = new QLineEdit(this);
  QLineEdit *pwLineEdit = new QLineEdit(this);
  QPushButton *okButton = new QPushButton(tr("Ok"), this);
  QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);

  nameLabel->setGeometry(9, 9, 40, 25);
  nameLineEdit->setGeometry(55, 9, 50 + w, 25);
  pwLabel->setGeometry(9, 40, 40, 25);
  pwLineEdit->setGeometry(55, 40, 50 + w, 25);
  okButton->setGeometry(150 + w, 9, 85, 25);
  cancelButton->setGeometry(150 + w, 40, 85, 25);
}
