#include <QtCore/qglobal.h>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtCore/QCoreApplication>

void Read(QString FileName) {
  QFile mFile(FileName);

  if (!mFile.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << "could not open file for read";
    return;
  }

  QTextStream in(&mFile);
  QString mText = in.readAll();
  qDebug() << mText;

  mFile.close();
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  Read(":/13.pro");

  return a.exec();
}
