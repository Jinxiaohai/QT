/**
 ** This file is part of the Dom project.
 ** Copyright 2018 jinxiaohai <xiaohaijin@outlook.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <QtCore/QCoreApplication>
#include <QtCore/qglobal.h>

#include <QtXml>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QDomDocument doc;
  QFile file("./my.xml");

  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "error !!!!";
    return 0;
  }
  if (!doc.setContent(&file)) {
    file.close();
    qDebug() << "error !!!!";
    return 0;
  }

  file.close();
  /// the first node.
  QDomNode firstNode = doc.firstChild();
  qDebug() << qPrintable(firstNode.nodeName())
           << qPrintable(firstNode.nodeValue());

  QDomElement docElem = doc.documentElement();
  QDomNode n = docElem.firstChild();
  while (!n.isNull()) {
    if (n.isElement()) {
      QDomElement e = n.toElement();
      qDebug() << qPrintable(e.tagName()) << qPrintable(e.attribute("id"));
      QDomNodeList list = e.childNodes();

      for (int i = 0; i < list.count(); ++i) {
        QDomNode node = list.at(i);
        if (node.isElement()) {
          qDebug() << "   " << qPrintable(node.toElement().tagName())
                   << qPrintable(node.toElement().text());
        }
      }  // for
    }    // if
    n = n.nextSibling();
  }  // while

  return a.exec();
}
