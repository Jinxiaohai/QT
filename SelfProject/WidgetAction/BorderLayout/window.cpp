#include <QLabel>
#include <QTextBrowser>

#include "borderlayout.h"
#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent) {
  QTextBrowser *centralWidget = new QTextBrowser;
  centralWidget->setPlainText(tr("Central Widget"));

  BorderLayout *layout = new BorderLayout;
  layout->addWidget(centralWidget, BorderLayout::Center);
  layout->addWidget(createLabel(tr("North")), BorderLayout::North);
  layout->addWidget(createLabel(tr("West")), BorderLayout::West);
  layout->addWidget(createLabel(tr("East 1")), BorderLayout::East);
  layout->addWidget(createLabel(tr("East 2")), BorderLayout::East);
  layout->addWidget(createLabel(tr("South")), BorderLayout::South);
  this->setLayout(layout);

  this->setWindowTitle(tr("Border Layout"));
}

Window::~Window() {}

QLabel *Window::createLabel(const QString &text) {
  QLabel *label = new QLabel(text);
  label->setFrameStyle(QFrame::Box | QFrame::Raised);
  return label;
}
