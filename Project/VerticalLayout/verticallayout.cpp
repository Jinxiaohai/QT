#include "verticallayout.h"
#include "ui_verticallayout.h"

VerticalLayout::VerticalLayout(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::VerticalLayout)
{
  ui->setupUi(this);
}

VerticalLayout::~VerticalLayout()
{
  delete ui;
}

void VerticalLayout::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
    }
}
