#include <QtWidgets>

#include "mainwindow.h"
#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"
#include "spreadsheet.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  spreadsheet = new Spreadsheet;
  setCentralWidget(spreadsheet);

  createActions();
  createMenus();
  createContextMenu();
  createToolBars();
  createStatusBar();

  readSettings();

  findDialog = 0;

  setWindowIcon(QIcon(":/images/icon.png"));
  setCurrentFile("");
}

MainWindow::~MainWindow() {}

void MainWindow::createActions() {
  newAction = new QAction(tr("&New"), this);
  newAction->setIcon(QIcon(":/images/new.png"));
  newAction->setShortcut(QKeySequence::New);
  newAction->setStatusTip(tr("Create a new spreadsheet file"));
  connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

  openAction = new QAction(tr("Open..."), this);
  openAction->setIcon(QIcon(":/images/open.png"));
  openAction->setShortcut(QKeySequence::Open);
  openAction->setStatusTip(tr("Open an existing spreadsheet file"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction(tr("&Save"), this);
  saveAction->setIcon(QIcon(":/images/save.png"));
  saveAction->setShortcut(QKeySequence::Save);
  saveAction->setStatusTip(tr("Save the spreadsheet to disk"));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  saveAsAction = new QAction(tr("Save &As"), this);
  saveAsAction->setStatusTip(tr("Save the spreadsheet under a new name"));
  connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

  for (int i = 0; i < MaxRecentFiles; ++i) {
    recentFileActions[i] = new QAction(this);
    recentFileActions[i]->setVisible(false);
    connect(recentFileActions[i], SIGNAL(triggered()), this,
            SLOT(openRecentFile()));
  }

  exitAction = new QAction(tr("E&xit"), this);
  exitAction->setShortcut(tr("Ctrl+Q"));
  exitAction->setStatusTip(tr("Exit the application"));
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

  cutAction = new QAction(tr("&Cut"), this);
  cutAction->setIcon(QIcon(":/images/cut.png"));
  cutAction->setShortcut(QKeySequence::Cut);
  cutAction->setStatusTip(
      tr("Cut the current selection's contents to  the clipboard"));
  connect(cutAction, SIGNAL(triggered()), spreadsheet, SLOT(cut));

  copyAction = new QAction(tr("&Copy"), this);
  copyAction->setIcon(QIcon(tr(":/images/copy.png")));
  copyAction->setShortcut(QKeySequence::Copy);
  copyAction->setStatusTip(
      tr("Copy the current selection's contents to the clipboard"));
}
