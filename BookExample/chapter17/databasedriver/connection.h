#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnetion() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("my.db");
  if (!db.open()) {
    QMessageBox::critical(0, "Cannot open database",
                          "Unable to establish a database conection.",
                          QMessageBox::Cancel);
    return false;
  }

  QSqlQuery querry;
  querry.exec("create table student (id int primary key, name varchar(20))");
  querry.exec("insert into student values(0, 'LiMing')");
  querry.exec("insert into student values(1, 'Xiaohai')");
  querry.exec("insert into student values(2, 'qiuyu')");
  return true;
}

#endif  // CONNECTION_H
