#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPixmap>
#include <QTextEdit>

#include "Menus.h"
#include "QssStyle.h"

Menus::Menus(QWidget *parent) : QMainWindow(parent) {
  createFileMenu();
  createEditMenu();
  createHelpMenu();

  m_editor = new QTextEdit(this);
  this->setCentralWidget(m_editor);
  this->statusBar();

  this->setWindowTitle(tr("Qt Projects"));
  this->resize(600, 400);

  QssStyle::setStyle(tr(":/resouce/myqss.qss"));
}

Menus::~Menus() {}

void Menus::fileOpen() { this->m_editor->append(tr("File Open selected")); }

void Menus::fileSave() { this->m_editor->append(tr("File Save selected")); }

void Menus::editNormal() { this->m_editor->append(tr("Edit Normal selected")); }

void Menus::editBold() { this->m_editor->append(tr("Edit Bold selected")); }

void Menus::editUnderline() {
  this->m_editor->append(tr("Edit Underline selected"));
}

void Menus::editAdvancedFont() {
  this->m_editor->append(tr("Advanced Font selected"));
}

void Menus::editAdvancedStyle() {
  this->m_editor->append(tr("Advanced Style selected"));
}

void Menus::editAdvancedUnderline() {
  this->m_editor->append(tr("Advanced Underline selected"));
}

void Menus::helpAbout() {
  QMessageBox::about(this, tr("About Menus"),
                     tr("This example implements an in-place ActiveX control "
                        "with menus and status messages."));
}

void Menus::helpAboutQt() { QMessageBox::aboutQt(this, tr("About Qt")); }

void Menus::createFileMenu() {
  QMenu *fileMenu = new QMenu(tr("file"), this);

  QAction *openAction =
      new QAction(QIcon(QPixmap(":/images/open.png")), tr("&Open"), this);
  openAction->setShortcut(tr("CTRL+O"));
  connect(openAction, &QAction::triggered, this, &Menus::fileOpen);
  fileMenu->addAction(openAction);

  QAction *saveAction =
      new QAction(QIcon(QPixmap(":/images/save.png")), tr("&Save"), this);
  saveAction->setShortcut(tr("CTRL+S"));
  connect(saveAction, &QAction::triggered, this, &Menus::fileSave);
  fileMenu->addAction(saveAction);

  this->menuBar()->addMenu(fileMenu);
}

void Menus::createEditMenu() {
  QMenu *editMenu = new QMenu(tr("edit"), this);

  QAction *normalEditAction = new QAction(tr("Normal"), this);
  normalEditAction->setShortcut(tr("CTRL+N"));
  normalEditAction->setToolTip(tr("Normal"));
  normalEditAction->setStatusTip(tr("Toggles Normal"));
  normalEditAction->setCheckable(true);
  connect(normalEditAction, &QAction::triggered, this, &Menus::editNormal);
  editMenu->addAction(normalEditAction);

  QAction *boldEditAction = new QAction(tr("Bold"), this);
  boldEditAction->setShortcut(tr("CTRL+B"));
  boldEditAction->setToolTip(tr("Bold"));
  boldEditAction->setStatusTip(tr("Toggles Bold"));
  boldEditAction->setCheckable(true);
  connect(boldEditAction, &QAction::triggered, this, &Menus::editBold);
  editMenu->addAction(boldEditAction);

  QAction *underlineEditAction = new QAction(tr("Underline"), this);
  underlineEditAction->setShortcut(tr("CTRL+U"));
  underlineEditAction->setToolTip(tr("Underline"));
  underlineEditAction->setStatusTip(tr("Toggles Underline"));
  underlineEditAction->setCheckable(true);
  connect(underlineEditAction, &QAction::triggered, this,
          &Menus::editUnderline);
  editMenu->addAction(underlineEditAction);

  QMenu *advancedMenu = new QMenu(tr("&Advanced"));

  QAction *fontAction = new QAction(tr("&Font..."), this);
  connect(fontAction, &QAction::triggered, this, &Menus::editAdvancedFont);
  advancedMenu->addAction(fontAction);

  QAction *styleAction = new QAction(tr("&Style..."), this);
  connect(styleAction, &QAction::triggered, this, &Menus::editAdvancedStyle);
  advancedMenu->addAction(styleAction);

  editMenu->addMenu(advancedMenu);
  editMenu->addSeparator();

  QAction *underlineAction = new QAction(tr("Una&vailable"), this);
  underlineAction->setShortcut(tr("CTRL+V"));
  underlineAction->setCheckable(true);
  underlineAction->setEnabled(false);
  connect(underlineAction, &QAction::triggered, this,
          &Menus::editAdvancedUnderline);
  editMenu->addAction(underlineAction);

  this->menuBar()->addMenu(editMenu);
}

void Menus::createHelpMenu() {
  QMenu *helpMenu = new QMenu(tr("help"), this);

  QAction *aboutAction = new QAction(tr("&About..."), this);
  aboutAction->setShortcut(tr("F1"));
  connect(aboutAction, &QAction::triggered, this, &Menus::helpAbout);
  helpMenu->addAction(aboutAction);

  QAction *aboutQtAction = new QAction(tr("About Qt"), this);
  connect(aboutQtAction, &QAction::triggered, this, &Menus::helpAboutQt);
  helpMenu->addAction(aboutQtAction);

  this->menuBar()->addMenu(helpMenu);
}
