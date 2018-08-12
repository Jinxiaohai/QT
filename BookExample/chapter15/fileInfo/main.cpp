#include <QCoreApplication>
#include <QFileInfo>
#include <QStringList>
#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QFile file("myfile.txt");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << file.errorString();
  }
  file.write("hello hirg");
  file.close();

  QFileInfo info(file);
  qDebug() << QObject::tr("absolutePaht: ") << info.absoluteFilePath() << endl
           << QObject::tr("filename: ") << info.fileName() << endl
           << QObject::tr("basename") << info.baseName() << endl
           << QObject::tr("suffix: ") << info.suffix() << endl
           << QObject::tr("create time: ") << info.created() << endl
           << QObject::tr("size: ") << info.size();

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << file.errorString();
  }
  qDebug() << QObject::tr("content is: ") << endl << file.readAll();
  qDebug() << QObject::tr("position is: ") << endl << file.pos();
  file.seek(0);

  // QByteArray array;
  // array = file.read(5);

  return a.exec();
}
