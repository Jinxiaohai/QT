#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QVariant>

#include "connection.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  //  qDebug() << "Available drivers: ";
  //  QStringList drivers = QSqlDatabase::drivers();
  //  foreach(QString driver, drivers) { qDebug() << driver; }

  if (!createConnetion()) {
    return -1;
  }
  QSqlQuery query;
  query.exec("select * from student");
  while (query.next()) {
    qDebug() << query.value(0).toInt() << query.value(1).toString();
  }
  return app.exec();
}
