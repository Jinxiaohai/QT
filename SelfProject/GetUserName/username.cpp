#include <QFile>
#include <QTextStream>

#include "username.h"

UserName::UserName() {}

QStringList UserName::getUsersName() {
  QFile file("/etc/passwd");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug("error");
  }

  QTextStream in(&file);
  while (!in.atEnd()) {
    QString eachLine = in.readLine();
    QStringList eachLineList = eachLine.split(":");
    if (eachLineList.at(2).toInt() >= 1000) {
      usersName.append(eachLineList.at(0));
    }
  }

  return usersName;
}
