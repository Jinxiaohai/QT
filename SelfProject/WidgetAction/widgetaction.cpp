#include <QLabel>
#include <QLineEdit>
#include <QSplitter>

#include "widgetaction.h"

WidgetAction::WidgetAction(QWidget *parent) : QWidgetAction(parent) {
  lineEdit = new QLineEdit;
  connect(lineEdit, &QLineEdit::returnPressed, this, &WidgetAction::sendText);
}

QWidget *WidgetAction::createWidget(QWidget *parent) {
  if (parent->inherits("QMenu") || parent->inherits("QToolBar")) {
    QSplitter *splitter = new QSplitter(parent);
    QLabel *label = new QLabel;
    label->setText(tr("insert text:"));
    splitter->addWidget(label);
    splitter->addWidget(lineEdit);
    return splitter;
  }
  return 0;
}

void WidgetAction::sendText() {
  emit getText(lineEdit->text());
  lineEdit->clear();
}
