#include "mysax.h"
#include <QtXml>
#include <QListWidget>

MySAX::MySAX() {
  list = new QListWidget;
  list->show();
}

MySAX::~MySAX() { delete list; }

bool MySAX::reaxdFile(const QString& fileName) {
  QFile file(fileName);
  QXmlInputSource inputSource(&file);
  QXmlSimpleReader reader;
  reader.setContentHandler(this);
  reader.setErrorHandler(this);
  return reader.parse(inputSource);
}

/**
  * @brief
  * @param
  * @param
  * @return
  */
bool MySAX::endElement(const QString& namespaceURI, const QString& localName,
                       const QString& qName) {
  currentText = ch;
  return true;
}

bool MySAX::startElement(const QString& namespaceURI, const QString& localName,
                         const QString& qName, const QXmlAttributes& atts) {
  if (qName == "library") {
    list->addItem(qName);
  } else if (qName == "book") {
    list->addItem("    " + qName + atts.value("id"));
  }
  return true;
}
