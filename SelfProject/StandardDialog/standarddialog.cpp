#include "standarddialog.h"
#include <QColorDialog>
#include <QDebug>
#include <QErrorMessage>
#include <QFileDialog>
#include <QFontDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QProgressDialog>
#include <QPushButton>
#include <QWizardPage>

#include "QssStyle.h"

StandardDialog::StandardDialog(QWidget *parent) : QMainWindow(parent) {
  QssStyle::setStyle(":myqss.qss");
  /// color dialog
  colorPushButton = new QPushButton;
  colorPushButton->setText(tr("color dialog"));
  connect(colorPushButton, &QPushButton::clicked, this,
          &StandardDialog::showColorDialog);

  filePushButton = new QPushButton;
  filePushButton->setText(tr("file dialog"));
  connect(filePushButton, &QPushButton::clicked, this,
          &StandardDialog::showFileDialog);

  fontPushButton = new QPushButton;
  fontPushButton->setText(tr("font dialog"));
  connect(fontPushButton, &QPushButton::clicked, this,
          &StandardDialog::showFontDialog);

  inputPushButton = new QPushButton;
  inputPushButton->setText(tr("input dialog"));
  connect(inputPushButton, &QPushButton::clicked, this,
          &StandardDialog::showInputDialog);

  messagePushButton = new QPushButton;
  messagePushButton->setText(tr("message dialog"));
  connect(messagePushButton, &QPushButton::clicked, this,
          &StandardDialog::showMessageDialog);

  progressPushButton = new QPushButton;
  progressPushButton->setText(tr("progress dialog"));
  connect(progressPushButton, &QPushButton::clicked, this,
          &StandardDialog::showProgressDialog);

  errordlg = new QErrorMessage;
  errorMessagePushButton = new QPushButton;
  errorMessagePushButton->setText(tr("error message dialog"));
  connect(errorMessagePushButton, &QPushButton::clicked, this,
          &StandardDialog::showErrorMessageDialog);

  wizardPagePushButton = new QPushButton;
  wizardPagePushButton->setText(tr("wizard page dialog"));
  connect(wizardPagePushButton, &QPushButton::clicked, this,
          &StandardDialog::showWizardDialog);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(colorPushButton, 0, 0, 1, 1);
  layout->addWidget(filePushButton, 1, 0, 1, 1);
  layout->addWidget(fontPushButton, 0, 1, 1, 1);
  layout->addWidget(inputPushButton, 1, 1, 1, 1);
  layout->addWidget(messagePushButton, 2, 0, 1, 2);
  layout->addWidget(progressPushButton, 3, 0, 1, 2);
  layout->addWidget(errorMessagePushButton, 4, 0, 1, 1);
  layout->addWidget(wizardPagePushButton, 4, 1, 1, 1);

  widget = new QWidget(this);
  widget->setLayout(layout);
  setCentralWidget(widget);

  resize(400, 200);
}

void StandardDialog::showColorDialog() {
  //  QColor color = QColorDialog::getColor(Qt::red, this, tr("color dialog"));
  //  qDebug() << "color: " << color;

  QColorDialog dialog(Qt::red, this);
  dialog.setOption(QColorDialog::ShowAlphaChannel);
  dialog.exec();
  QColor color = dialog.currentColor();
  qDebug() << "color: " << color;
}

void StandardDialog::showFileDialog() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("file dialog"), "/home/xiaohai", tr("image file(* png * jpg)"));
  qDebug() << "fileName: " << fileName;
}

void StandardDialog::showFontDialog() {
  bool ok;
  QFont font = QFontDialog::getFont(&ok, this);
  if (ok) {
    fontPushButton->setFont(font);
  } else {
    qDebug() << tr("please select a font");
  }
}

void StandardDialog::showInputDialog() {
  bool ok;
  QString string =
      QInputDialog::getText(this, tr("input dialog"), tr("input username: "),
                            QLineEdit::Normal, tr("admin"), &ok);
  if (ok) {
    qDebug() << "string: " << string;
  }

  int value =
      QInputDialog::getInt(this, tr("input integer dialog"), tr("-1000, 1000"),
                           100, -1000, 1000, 10, &ok);
  if (ok) {
    qDebug() << "value: " << value;
  }

  double value2 =
      QInputDialog::getDouble(this, tr("input double dialog"),
                              tr("-1000.0, 1000.0"), 0.00, -1000, 1000, 2, &ok);
  if (ok) {
    qDebug() << "value2: " << value2;
  }

  QStringList items;
  items << tr("item1") << tr("item2");
  QString item =
      QInputDialog::getItem(this, tr("input item dialog"),
                            tr("input the next item"), items, 0, true, &ok);
  if (ok) {
    qDebug() << "item: " << item;
  }
}

void StandardDialog::showMessageDialog() {
  int ret1 = QMessageBox::question(this, tr("question dialog"),
                                   tr("do you know the HIRG ?"),
                                   QMessageBox::Yes, QMessageBox::No);
  if (ret1 == QMessageBox::Yes) {
    qDebug() << tr("question");
  }

  int ret2 = QMessageBox::information(this, tr("infomation dialog"),
                                      tr("I'm xiaohai."), QMessageBox::Ok);
  if (ret2 == QMessageBox::Ok) {
    qDebug() << tr("infomation dialog.");
  }

  int ret3 = QMessageBox::warning(this, tr("warning dialog"),
                                  tr("don't stop the process in early"),
                                  QMessageBox::Abort);
  if (ret3 == QMessageBox::Abort) {
    qDebug() << tr("warning dialog");
  }

  int ret4 = QMessageBox::critical(this, tr("error dialog"),
                                   tr("find a error..."), QMessageBox::YesAll);
  if (ret4 == QMessageBox::YesAll) {
    qDebug() << tr("error");
  }

  QMessageBox::about(this, tr("about dialog"), tr("This is a Qt program..."));
}

void StandardDialog::showProgressDialog() {
  QProgressDialog dialog(tr("copy progress"), tr("Cannel"), 0, 500000, this);
  dialog.setWindowTitle(tr("progress dialog"));
  dialog.setWindowModality(Qt::WindowModal);
  dialog.show();

  for (int i = 0; i != 500000; ++i) {
    dialog.setValue(i);
    QCoreApplication::processEvents();
    if (dialog.wasCanceled()) {
      return;
    }
  }
  dialog.setValue(5000000);
  qDebug() << tr("copy done");
}

void StandardDialog::showErrorMessageDialog() {
  errordlg->setWindowTitle("error message dialog");
  errordlg->showMessage(tr("This is error message dialog."));
}

void StandardDialog::showWizardDialog() {
  QWizard wizard(this);
  wizard.setWindowTitle(tr("wizard dialog"));
  wizard.addPage(createPage1());
  wizard.addPage(createPage2());
  wizard.addPage(createPage3());
  wizard.exec();
}

QWizardPage *StandardDialog::createPage1() {
  QWizardPage *page = new QWizardPage;
  page->setTitle(tr("Introduction."));
  return page;
}

QWizardPage *StandardDialog::createPage2() {
  QWizardPage *page = new QWizardPage;
  page->setTitle(tr("user information."));
  return page;
}

QWizardPage *StandardDialog::createPage3() {
  QWizardPage *page = new QWizardPage;
  page->setTitle(tr("Exit."));
  return page;
}
