#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "layout.h"
#include "ui_layout.h"

Layout::Layout(QWidget *parent) : QWidget(parent), ui(new Ui::Layout) {
  ui->setupUi(this);

  QLabel *lb = new QLabel(this);
  lb->setText(tr("ID:"));
  lb->setGeometry(10, 10, 40, 20);

  QLineEdit *leID = new QLineEdit(tr("zml"), this);
  leID->setGeometry(50, 10, 50, 20);

  QLabel *lb1 = new QLabel(this);
  lb1->setText(tr("psswd:"));
  lb1->setGeometry(10, 40, 40, 20);

  QLineEdit *lePwd = new QLineEdit(tr("123456"), this);
  lePwd->setGeometry(50, 40, 50, 20);

  QPushButton *btn = new QPushButton(tr("quit"), this);
  btn->setGeometry(50, 70, 50, 20);
}

Layout::~Layout() { delete ui; }

void Layout::changeEvent(QEvent *e) {
  QWidget::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}
