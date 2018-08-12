#include "mywidget.h"
#include "ui_mywidget.h"

#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProgressDialog>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MyWidget) {
  ui->setupUi(this);
}

MyWidget::~MyWidget() { delete ui; }

void MyWidget::changeEvent(QEvent *e) {
  QWidget::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void MyWidget::on_pushButton_clicked() {
  QColorDialog dialog(Qt::red, this);
  dialog.setOption(QColorDialog::ShowAlphaChannel);
  dialog.exec();
  QColor color = dialog.currentColor();
  qDebug() << "color: " << color;
}

void MyWidget::on_pushButton_2_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("file dialog"), "/home/xiaohai", tr("figure...(* png * jpg)"));
  qDebug() << "fileName: " << fileName;
}

void MyWidget::on_pushButton_3_clicked() {
  bool ok;
  QFont font = QFontDialog::getFont(&ok, this);
  if (ok) {
    ui->pushButton_3->setFont(font);
  } else {
    qDebug() << tr("no font found");
  }
}

void MyWidget::on_pushButton_4_clicked() {
  bool ok;
  QString string =
      QInputDialog::getText(this, tr("input dialog"), tr("input username:"),
                            QLineEdit::Normal, tr("admin"), &ok);
  if (ok) {
    qDebug() << "string: " << string;
  }
  int value = QInputDialog::getInt(this, tr("input integer dialog:"),
                                   tr("range from -1000 to 1000"), 100, -1000,
                                   1000, 10, &ok);
  if (ok) {
    qDebug() << "value: " << value;
  }
}

void MyWidget::on_pushButton_5_clicked() {
  int ret1 =
      QMessageBox::question(this, tr("question dialog"), tr("Do you know Qt ?"),
                            QMessageBox::Yes, QMessageBox::No);
  if (ret1 == QMessageBox::Yes) {
    qDebug() << tr("question!");
  }
  int ret2 = QMessageBox::information(this, tr("information dialog"),
                                      tr("This is Qt book"), QMessageBox::Ok);
  if (ret2 == QMessageBox::Ok) {
    qDebug() << tr("information!");
  }
  int ret3 = QMessageBox::warning(this, tr("warning dialog"),
                                  tr("tiqianjieshu"), QMessageBox::Abort);
  if (ret3 == QMessageBox::Abort) {
    qDebug() << "warning!";
  }
  int ret4 = QMessageBox::critical(this, tr("error"), tr("find a fatal error"),
                                   QMessageBox::YesAll);
  if (ret4 == QMessageBox::YesAll) {
    qDebug() << tr("fatal error");
  }
}

void MyWidget::on_pushButton_6_clicked() {
  QProgressDialog dialog(tr("progress"), tr("cancel"), 0, 5000000, this);
  dialog.setWindowTitle(tr("progress dialog"));
  dialog.setWindowModality(Qt::WindowModal);
  dialog.show();

  for (int i = 0; i != 5000000; ++i) {
    dialog.setValue(i);
    QCoreApplication::processEvents();
    if (dialog.wasCanceled()) {
      break;
    }
    dialog.setValue(5000000);
    qDebug() << tr("copy done.");
  }
}
