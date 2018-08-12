#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QFont>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QProgressDialog>
#include <QPushButton>

#include "progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent) : QDialog(parent) {
  QFont font("ZYSong18030", 12);
  this->setFont(font);
  this->setWindowTitle(tr("Progress"));

  FileNum = new QLabel;
  FileNum->setText(tr("The total files: "));

  FileNumLineEdit = new QLineEdit;
  FileNumLineEdit->setText(tr("100000"));

  ProgressType = new QLabel;
  ProgressType->setText(tr("The file type: "));

  comboBox = new QComboBox;
  comboBox->addItem(tr("progress Bar"));
  comboBox->addItem(tr("progress Dialog"));

  progressBar = new QProgressBar;

  startBtn = new QPushButton();
  startBtn->setText(tr("Start"));

  mainLayout = new QGridLayout(this);
  mainLayout->addWidget(FileNum, 0, 0);
  mainLayout->addWidget(FileNumLineEdit, 0, 1);
  mainLayout->addWidget(ProgressType, 1, 0);
  mainLayout->addWidget(comboBox, 1, 1);
  mainLayout->addWidget(progressBar, 2, 0, 1, 2);
  mainLayout->addWidget(startBtn, 3, 1);
  mainLayout->setMargin(15);
  mainLayout->setSpacing(10);
  connect(startBtn, SIGNAL(clicked()), this, SLOT(startProgress()));
}

ProgressDialog::~ProgressDialog() {}

void ProgressDialog::startProgress() {
  bool Ok = true;
  int num = FileNumLineEdit->text().toInt(&Ok);

  if (comboBox->currentIndex() == 0) {
    progressBar->setRange(0, num);
    for (int i = 1; i <= num; ++i) {
      progressBar->setValue(i);
    }
  } else if (comboBox->currentIndex() == 1) {
    QProgressDialog *progressDialog = new QProgressDialog(this);
    QFont font("ZYSong18030", 12);
    progressDialog->setFont(font);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setMinimumDuration(5);
    progressDialog->setLabelText(tr("Please wait"));
    progressDialog->setCancelButtonText(tr("Cancel"));
    progressDialog->setRange(0, num);
    for (int i = 1; i <= num; ++i) {
      progressDialog->setValue(i);
      if (progressDialog->wasCanceled()) {
        return;
      }
    }
  }
}
