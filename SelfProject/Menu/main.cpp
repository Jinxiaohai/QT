#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  XIAOHAI::MainWindow w;
  w.show();

  return a.exec();
}
