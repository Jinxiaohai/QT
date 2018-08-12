#include <QDebug>
#include <QDir>

#include <QtCore/qglobal.h>
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QDir dir("/home/xiaohai/Desktop");
  dir.setFilter(QDir::Files);
  qDebug() << dir.entryInfoList();

  dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  qDebug() << dir.entryList();

  return a.exec();
}
