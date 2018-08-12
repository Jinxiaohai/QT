#include <QtCore/qglobal.h>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QFileInfo fileInfo("/home/xiaohai/Desktop");
  qDebug() << fileInfo.path();
  qDebug() << fileInfo.absoluteDir();
  qDebug() << fileInfo.absoluteFilePath();
  qDebug() << fileInfo.absolutePath();
  qDebug() << fileInfo.filePath();
  qDebug() << fileInfo;

  return a.exec();
}
