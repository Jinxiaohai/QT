#include <QCloseEvent>
#include <QIcon>
#include <QMenuBar>
#include <QSettings>
#include <QSplitter>
#include <QStatusBar>
#include <QStyle>
#include <QTextEdit>
#include <QTreeWidget>

#include "mailsplitter.h"

MailSplitter::MailSplitter(QWidget *parent) : QMainWindow(parent) {
  QIcon folderIcon(style()->standardPixmap(QStyle::SP_DirClosedIcon));
  QIcon trashIcon(style()->standardPixmap(QStyle::SP_FileIcon));

  QStringList folderLabels;
  folderLabels << tr("Folders");

  foldersTreeWidget = new QTreeWidget;
  foldersTreeWidget->setHeaderLabels(folderLabels);
  this->addFolder(folderIcon, tr("Inbox"));
  this->addFolder(folderIcon, tr("Outbox"));
  this->addFolder(folderIcon, tr("Sent"));
  this->addFolder(trashIcon, tr("Trash"));

  QStringList messageLabels;
  messageLabels << tr("Subject") << tr("Sender") << tr("Date");

  messagesTreeWidget = new QTreeWidget;
  messagesTreeWidget->setHeaderLabels(messageLabels);
  addMessage(tr("Happy New Year!"), tr("Grace K. <grace@software-inc.com>"), tr("2006-12-31"));
  addMessage(tr("Radically new concept!"), tr("Grace K. <grace@software-inc.com>"), tr("2006-12-22"));
  addMessage(tr("Accounts"), tr("pascale@nospam.com"), tr("2006-12-31"));
  addMessage(tr("Expenses"), tr("Joe Bloggs <joe@bloggs.com>"), tr("2006-12-25"));
  addMessage(tr("Re: Expenses"), tr("Andy <andy@nospam.com>"), tr("2007-01-02"));
  addMessage(tr("Re: Accounts"), tr("Joe Bloggs <joe@bloggs.com>"), tr("2007-01-03"));
  addMessage(tr("Re: Accounts"), tr("Andy <andy@nospam.com>"), tr("2007-01-03"));
  messagesTreeWidget->resizeColumnToContents(0);
  messagesTreeWidget->resizeColumnToContents(1);

  textEdit = new QTextEdit;
  textEdit->setReadOnly(true);
  textEdit->setText(tr("xiaohaijin@outlook.com\n jinxiaohai\n SINAP"));

  //  QMenu *fileMenu = new QMenu("&File", this);
  //  menuBar()->addMenu(fileMenu);
  //  QAction *newAction = new QAction("&New", this);
  //  fileMenu->addAction(newAction);

  menuBar()->addMenu(tr("&File"));
  menuBar()->addMenu(tr("&Edit"));
  menuBar()->addMenu(tr("&View"));
  menuBar()->addMenu(tr("F&older"));
  menuBar()->addMenu(tr("&Message"));
  menuBar()->addMenu(tr("&Setting"));
  menuBar()->addMenu(tr("&Help"));
  statusBar()->showMessage(tr("No new message on server"));

  rightSplitter = new QSplitter(Qt::Vertical);
  rightSplitter->addWidget(messagesTreeWidget);
  rightSplitter->addWidget(textEdit);
  rightSplitter->setStretchFactor(1, 1);

  mainSplitter = new QSplitter(Qt::Horizontal);
  mainSplitter->addWidget(foldersTreeWidget);
  mainSplitter->addWidget(rightSplitter);
  mainSplitter->setStretchFactor(1, 1);

  this->setCentralWidget(mainSplitter);
  this->setWindowTitle(tr("Mail Client"));
  readSettings();
}

MailSplitter::~MailSplitter() {}

void MailSplitter::closeEvent(QCloseEvent *event) {
  writeSettings();
  event->accept();
}

void MailSplitter::addFolder(const QIcon &icon, const QString &name) {
  QTreeWidgetItem *root;
  if (foldersTreeWidget->topLevelItemCount() == 0) {
    root = new QTreeWidgetItem(foldersTreeWidget);
    root->setText(0, tr("Mail"));
    foldersTreeWidget->setItemExpanded(root, true);
  } else {
    root = foldersTreeWidget->topLevelItem(0);
  }

  QTreeWidgetItem *newItem = new QTreeWidgetItem(root);
  newItem->setText(0, name);
  newItem->setIcon(0, icon);

  if (!foldersTreeWidget->currentItem()) {
    foldersTreeWidget->setCurrentItem(newItem);
  }
}

void MailSplitter::addMessage(const QString &subject, const QString &from, const QString &date) {
  QTreeWidgetItem *newItem = new QTreeWidgetItem(messagesTreeWidget);
  newItem->setText(0, subject);
  newItem->setText(1, from);
  newItem->setText(2, date);

  if (!messagesTreeWidget->currentItem()) {
    messagesTreeWidget->setCurrentItem(newItem);
  }
}

void MailSplitter::readSettings() {
  QSettings settings("Software Inc.", "Mail Client");

  settings.beginGroup("mainWindow");
  restoreGeometry(settings.value("geometry").toByteArray());
  mainSplitter->restoreState(settings.value("mainSplitter").toByteArray());
  rightSplitter->restoreState(settings.value("rightSplitter").toByteArray());
  settings.endGroup();
}

void MailSplitter::writeSettings() {
  QSettings settings("Software Inc.", "Mail Client");

  settings.beginGroup("mainWindow");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("mainSplitter", mainSplitter->saveState());
  settings.setValue("rightSplitter", rightSplitter->saveState());
  settings.endGroup();
}
