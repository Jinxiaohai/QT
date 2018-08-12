#ifndef MYSAX_H
#define MYSAX_H

#include <QtCore/qglobal.h>
#include <QXmlDefaultHandler>

class QListWidget;
class MySAX : public QXmlDefaultHandler {
 public:
  MySAX();
  ~MySAX();
  bool reaxdFile(const QString &fileName);

 protected:
  bool startElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName, const QXmlAttributesPrivate &atts);
  bool endElement(const QString &namespaceURI, const QString &localName,
                  const QString &qName);

 private:
  QListWidget *list;
  QString currentText;
};

#endif  // MYSAX_H
