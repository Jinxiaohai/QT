#include <QCheckBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent) : QDialog(parent) {
  label = new QLabel(tr("&What"));
  lineEdit = new QLineEdit;
  label->setBuddy(lineEdit);

  caseCheckBox = new QCheckBox(tr("&case sensitive"));
  backwardCheckBox = new QCheckBox(tr("&backward"));

  findButton = new QPushButton(tr("&Find"));
  findButton->setDefault(true);
  findButton->setEnabled(false);
  closeButton = new QPushButton(tr("Close"));

  connect(lineEdit, SIGNAL(textChanged(QString)), this,
          SLOT(enabledFindButton(QString)));
  connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

  QHBoxLayout *topLeftLayout = new QHBoxLayout;
  topLeftLayout->addWidget(label);
  topLeftLayout->addWidget(lineEdit);

  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addLayout(topLeftLayout);
  leftLayout->addWidget(caseCheckBox);
  leftLayout->addWidget(backwardCheckBox);

  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addWidget(findButton);
  rightLayout->addWidget(closeButton);
  rightLayout->addStretch();

  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addLayout(leftLayout);
  mainLayout->addLayout(rightLayout);

  this->setWindowTitle(tr("Xiaohai Project"));
  /// fixed the size;
  this->setFixedHeight(this->sizeHint().height());
  this->setFixedWidth(sizeHint().width());
}

FindDialog::~FindDialog() {}

void FindDialog::enabledFindButton(const QString &text) {
  findButton->setEnabled(!text.isEmpty());
}

void FindDialog::findClicked() {
  QString text = lineEdit->text();
  Qt::CaseSensitivity cs;
  if (caseCheckBox->isChecked()) {
    cs = Qt::CaseSensitive;
  } else {
    cs = Qt::CaseInsensitive;
  }

  if (backwardCheckBox->isChecked()) {
    emit findPrevious(text, cs);
    qDebug() << "Find Previous.";
  } else {
    emit findNext(text, cs);
    qDebug() << "Find Next.";
  }
}
