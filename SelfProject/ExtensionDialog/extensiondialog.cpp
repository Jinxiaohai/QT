#include <QComboBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "extensiondialog.h"

ExtensionDialog::ExtensionDialog(QWidget *parent) : QDialog(parent) {
  this->setWindowTitle(tr("Extension Dialog"));
  this->createBaseInfo();
  this->createDetailInfo();

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(baseWidget);
  layout->addWidget(detailWidget);
  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->setSpacing(10);
}

ExtensionDialog::~ExtensionDialog() {}

void ExtensionDialog::showDetailInfo() {
  if (detailWidget->isHidden()) {
    detailWidget->show();
  } else {
    detailWidget->hide();
  }
}

void ExtensionDialog::createBaseInfo() {
  baseWidget = new QWidget;

  QLabel *nameLabel = new QLabel(tr("name: "));
  QLineEdit *nameLineEdit = new QLineEdit;

  QLabel *sexLabel = new QLabel(tr("gender"));
  QComboBox *sexComboBox = new QComboBox;
  sexComboBox->insertItem(0, tr("female"));
  sexComboBox->insertItem(1, tr("male"));

  QGridLayout *LeftLayout = new QGridLayout;
  LeftLayout->addWidget(nameLabel, 0, 0);
  LeftLayout->addWidget(nameLineEdit, 0, 1);
  LeftLayout->addWidget(sexLabel, 1, 0);
  LeftLayout->addWidget(sexComboBox, 1, 1);

  QPushButton *OKBtn = new QPushButton(tr("Ok"));
  QPushButton *DetailBtn = new QPushButton(tr("Detail"));

  QDialogButtonBox *btnBox = new QDialogButtonBox(Qt::Vertical);
  btnBox->addButton(OKBtn, QDialogButtonBox::ActionRole);
  btnBox->addButton(DetailBtn, QDialogButtonBox::ActionRole);

  QHBoxLayout *mainLayout = new QHBoxLayout(baseWidget);
  mainLayout->addLayout(LeftLayout);
  mainLayout->addWidget(btnBox);

  connect(DetailBtn, SIGNAL(clicked()), this, SLOT(showDetailInfo()));
}

void ExtensionDialog::createDetailInfo() {
  detailWidget = new QWidget;

  QLabel *ageLabel = new QLabel(tr("Age"));
  QLineEdit *ageLineEdit = new QLineEdit;

  QLabel *departmentLabel = new QLabel(tr("Department"));
  QComboBox *departmentComboBox = new QComboBox;
  departmentComboBox->addItem(tr("department1"));
  departmentComboBox->addItem(tr("department2"));
  departmentComboBox->addItem(tr("department3"));
  departmentComboBox->addItem(tr("department4"));

  QLabel *emailLabel = new QLabel(tr("Email"));
  QLineEdit *emailLineEdit = new QLineEdit;

  QGridLayout *mainLayout = new QGridLayout(detailWidget);
  mainLayout->addWidget(ageLabel, 0, 0);
  mainLayout->addWidget(ageLineEdit, 0, 1);
  mainLayout->addWidget(departmentLabel, 1, 0);
  mainLayout->addWidget(departmentComboBox, 1, 1);
  mainLayout->addWidget(emailLabel, 2, 0);
  mainLayout->addWidget(emailLineEdit, 2, 1);

  detailWidget->hide();
}
