#include <QApplication>
#include <QSplashScreen>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QPixmap pixmap(":/images/background.jpg");
  QSplashScreen splash(pixmap);
  splash.show();
  a.processEvents();

  MainWindow w;
  w.show();

  splash.finish(&w);
  return a.exec();
}
