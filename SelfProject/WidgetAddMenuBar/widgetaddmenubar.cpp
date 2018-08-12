#include <QMenuBar>

#include "widgetaddmenubar.h"

WidgetAddMenuBar::WidgetAddMenuBar(QWidget *parent) : QWidget(parent) {}

WidgetAddMenuBar::~WidgetAddMenuBar() {
  menuBar = new QMenuBar(this);
  menuBar->setObjectName(QStringLiteral("menuBar"));
  menuBar->setGeometry(QRect(0, 0, 300, 15));

  menuBar->addMenu(tr("file"));
}
