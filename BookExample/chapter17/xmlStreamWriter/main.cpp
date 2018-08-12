#include <QtCore/QCoreApplication>
#include <QtCore/qglobal.h>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QFile file("my.xml");
  if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
    qDebug() << "Error: cannot open file.";
    return -1;
  }

  QXmlStreamWriter stream(&file);
  stream.setAutoFormatting(true);

  stream.writeStartDocument();
  stream.writeStartElement("book");
  stream.writeAttribute("href", "www.jinxiaohai.cn");
  stream.writeTextElement("title", "my site.");
  stream.writeEndElement();
  stream.writeEndDocument();

  file.close();
  qDebug() << "write finished .";
  return a.exec();
}
