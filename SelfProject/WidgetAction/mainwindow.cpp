#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgetaction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  WidgetAction *action = new WidgetAction;
  QMenu *editMenu = ui->menuBar->addMenu(tr("&Edit"));
  editMenu->addAction(action);
  connect(action, SIGNAL(getText(QString)), this, SLOT(setText(QString)));
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

void MainWindow::setText(const QString &string) {
  ui->textEdit->setText(string);
}
