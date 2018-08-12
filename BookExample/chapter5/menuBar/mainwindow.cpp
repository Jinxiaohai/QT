#include <QMenu>
#include <QtWidgets>
#include <QToolButton>
#include <QSpinBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  /// create a edit menu.
  QMenu *editMenu = ui->menuBar->addMenu(tr("Edit(&E)"));
  /// add action in menu.
  QAction *action_Open = editMenu->addAction(tr("Open(&O)"));
  action_Open->setShortcut(QKeySequence("Ctrl+o"));
  /// add action in mainToolBar.
  ui->mainToolBar->addAction(action_Open);

  QActionGroup *group = new QActionGroup(this);

  QAction *action_L = group->addAction(tr("Alignleft(&L)"));
  action_L->setCheckable(true);
  QAction *action_R = group->addAction(tr("Alignright(&R)"));
  action_R->setCheckable(true);
  QAction *action_C = group->addAction(tr("Aligncenter(&C)"));
  action_C->setCheckable(true);
  action_L->setChecked(true);

  editMenu->addSeparator();
  editMenu->addAction(action_L);
  editMenu->addAction(action_R);
  editMenu->addAction(action_C);

  QToolButton *toolBtn = new QToolButton(this);
  toolBtn->setText(tr("Color"));
  QMenu *colorMenu = new QMenu(this);
  colorMenu->addAction(tr("Red"));
  colorMenu->addAction(tr("Green"));
  toolBtn->setMenu(colorMenu);
  toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
  ui->mainToolBar->addWidget(toolBtn);
  QSpinBox *spinBox = new QSpinBox(this);
  ui->mainToolBar->addWidget(spinBox);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::changeEvent(QEvent *e) {
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}
