#include <QGridLayout>
#include <QPushButton>

#include "QssStyle.h"
#include "blackcrow.h"

BlackCrow::BlackCrow(QWidget *parent) : QWidget(parent) {
  QssStyle::setStyle(":/qdarkstyle/style.qss");
  QGridLayout *mainLayout = new QGridLayout(this);

  for (int i = 0; i != 4; ++i) {
    firstLine[i] = new QWidget;
    firstLine[i]->resize(100, 100);
    mainLayout->addWidget(firstLine[i], 1, i);
  }
  for (int i = 0; i != 4; ++i) {
    secondLine[i] = new QWidget;
    secondLine[i]->resize(100, 100);
    mainLayout->addWidget(secondLine[i], 2, i);
  }
  for (int i = 0; i != 4; ++i) {
    thirdLine[i] = new QWidget;
    thirdLine[i]->resize(100, 100);
    mainLayout->addWidget(thirdLine[i], 3, i);
  }

  this->resize(800, 600);
}

BlackCrow::~BlackCrow() {}
