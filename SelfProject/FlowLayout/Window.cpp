#include <QPushButton>

#include "FlowLayout.h"
#include "Window.h"

Window::Window(QWidget *parent) : QWidget(parent) {
  FlowLayout *flowLayout = new FlowLayout;
  flowLayout->addWidget(new QPushButton(tr("Short")));
  flowLayout->addWidget(new QPushButton(tr("Longer")));
  flowLayout->addWidget(new QPushButton(tr("Different text")));
  flowLayout->addWidget(new QPushButton(tr("More text")));
  flowLayout->addWidget(new QPushButton(tr("Even longer button text")));
  setLayout(flowLayout);

  setWindowTitle(tr("balabal"));
}
