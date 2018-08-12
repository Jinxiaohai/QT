#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QStackedWidget>

#include "QssStyle.h"
#include "stackdlg.h"

StackDlg::StackDlg(QWidget *parent) : QDialog(parent) {
  QssStyle::setStyle(":/myqss.qss");
  this->setWindowTitle(tr("Stacked Widget"));

  list = new QListWidget(this);
  list->insertItem(0, tr("Window1"));
  list->insertItem(1, tr("Window2"));
  list->insertItem(2, tr("Window3"));

  label1 = new QLabel(tr("Window Test1"));
  label2 = new QLabel(tr("Window Test2"));
  label3 = new QLabel(tr("Window Test3"));

  stack = new QStackedWidget(this);
  stack->addWidget(label1);
  stack->addWidget(label2);
  stack->addWidget(label3);

  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->setMargin(5);
  mainLayout->setSpacing(5);
  mainLayout->addWidget(list);
  mainLayout->addWidget(stack, 0, Qt::AlignHCenter);
  mainLayout->setStretchFactor(list, 1);
  mainLayout->setStretchFactor(stack, 3);
  connect(list, SIGNAL(currentRowChanged(int)), stack,
          SLOT(setCurrentIndex(int)));

  int width = sizeHint().width();
  int height = sizeHint().height();
  resize(2 * width, 2 * height);
}

StackDlg::~StackDlg() {}
