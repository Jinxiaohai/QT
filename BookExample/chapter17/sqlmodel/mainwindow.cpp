#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  /// QFile file("myqss.qss");
  /// if (!file.open(QIODevice::ReadOnly)) {
  ///  qDebug() << file.errorString();
  /// }
  /// QString qss;
  /// qss = file.readAll();
  /// this->setStyleSheet(qss);
  /// file.close();

  QSqlQueryModel *model = new QSqlQueryModel(this);
  model->setQuery("select * from student");
  model->setHeaderData(0, Qt::Horizontal, tr("id"));
  model->setHeaderData(1, Qt::Horizontal, tr("name"));
  model->setHeaderData(2, Qt::Horizontal, tr("course"));
  QTableView *view = new QTableView(this);
  view->setModel(model);
  setCentralWidget(view);
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
