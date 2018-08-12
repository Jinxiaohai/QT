#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

void Write(QString fileName) {
  QFile mFile(fileName);
  if (!mFile.open(QFile::WriteOnly | QFile::Text)) {
    qDebug() << "could not open file for write";
    return;
  }

  QTextStream out(&mFile);
  out << "Hello Qt";
  mFile.flush();

  mFile.close();

  return;
}

void Read(QString fileName) {
  QFile mFile(fileName);
  if (!mFile.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << "could not open file for read";
    return;
  }

  QString mText;
  mText = mFile.readAll();
  qDebug() << mText;

  return;
}

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  QString fileName = "/home/xiaohai/Desktop/Qt.txt";
  Write(fileName);
  Read(fileName);

  return app.exec();
}
