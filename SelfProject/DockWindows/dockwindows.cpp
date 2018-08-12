#include <QDockWidget>
#include <QTextEdit>

#include "QssStyle.h"
#include "dockwindows.h"

DockWindows::DockWindows(QWidget *parent) : QMainWindow(parent) {
  QssStyle::setStyle(":/myqss.qss");
  this->setWindowTitle(tr("DockWindows"));

  QTextEdit *textEdit = new QTextEdit(this);
  textEdit->setText(tr("Main Window"));
  textEdit->setAlignment(Qt::AlignCenter);

  this->setCentralWidget(textEdit);

  /// the first
  QDockWidget *dockUp = new QDockWidget(tr("Dock Widget Up"), this);
  dockUp->setFeatures(QDockWidget::DockWidgetMovable);
  dockUp->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  QTextEdit *textEditUp = new QTextEdit(dockUp);
  textEditUp->setText(
      tr("Window Up, The dock widget can be moved between docks by the user"));
  dockUp->setWidget(textEditUp);
  this->addDockWidget(Qt::RightDockWidgetArea, dockUp);

  /// the second
  QDockWidget *dockMiddle = new QDockWidget(tr("Dock widget Middle"), this);
  dockMiddle->setFeatures(QDockWidget::DockWidgetClosable |
                          QDockWidget::DockWidgetFloatable);
  QTextEdit *textEditMiddle = new QTextEdit(dockMiddle);
  textEditMiddle->setText(
      tr("Window Middle, The dock widget can be detached from tyhe main "
         "window, and floated as an independent window, and can be closed"));
  dockMiddle->setWidget(textEditMiddle);
  this->addDockWidget(Qt::RightDockWidgetArea, dockMiddle);

  /// the third
  QDockWidget *dockBottom = new QDockWidget(tr("Dock widget Bottom"), this);
  dockBottom->setFeatures(QDockWidget::AllDockWidgetFeatures);
  QTextEdit *textEditBottom = new QTextEdit(dockBottom);
  textEditBottom->setText(
      tr("Window Bottom, The dock widget can be closed, moved, and floated"));
  dockBottom->setWidget(textEditBottom);
  addDockWidget(Qt::RightDockWidgetArea, dockBottom);
}

DockWindows::~DockWindows() {}
