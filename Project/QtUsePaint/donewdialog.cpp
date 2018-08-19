#include <QColorDialog>

#include "donewdialog.h"
#include "ui_donewdialog.h"

DoNewDialog::DoNewDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::DoNewDialog) {
  ui->setupUi(this);
  backColor = Qt::white;
}

DoNewDialog::~DoNewDialog() { delete ui; }

int DoNewDialog::getWidth() const { return ui->widthSpinBox->text().toInt(); }

int DoNewDialog::getHeight() const { return ui->heightSpinBox->text().toInt(); }

QColor DoNewDialog::getBackColor() { return backColor; }

void DoNewDialog::changeEvent(QEvent *e) {
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void DoNewDialog::on_toolButton_clicked() {
  QColor newColor = QColorDialog::getColor(Qt::blue, this);
  if (newColor.isValid()) {
    backColor = newColor;
    QPalette palette = ui->textBrowser->palette();
    palette.setColor(QPalette::Base, backColor);
    ui->textBrowser->setPalette(palette);
    update();
  }
}
