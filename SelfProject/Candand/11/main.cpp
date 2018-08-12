#include <QtCore/qglobal.h>
#include <QDebug>
#include <QDir>
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QDir mDir("/home/xiaohai/Desktop");
  qDebug() << mDir.exists();

  foreach (QFileInfo mItm, mDir.drives()) {
    qDebug() << mItm.absoluteFilePath();
    qDebug() << mItm.size();
  }

  return a.exec();
}
