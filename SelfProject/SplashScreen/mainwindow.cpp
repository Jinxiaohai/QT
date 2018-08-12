#include <QTextEdit>
#include <QTime>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->setWindowTitle(tr("Splash Screen Example"));
  QTextEdit *textEdit = new QTextEdit;
  textEdit->setText(tr("Hello xiaohai"));

  this->setCentralWidget(textEdit);
  this->resize(600, 450);
}

MainWindow::~MainWindow() {}
