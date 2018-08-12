#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection() {
  QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE", "connection1");
  db1.setDatabaseName("my1.db");
  if (!db1.open()) {
    QMessageBox::critical(0, "Cannot open database1",
                          "Unable to establish a database",
                          QMessageBox::Cancel);
    return -1;
  }

  /// connection
  QSqlQuery query1(db1);
  query1.exec("create table student (id int primary key, name varchar(20))");
  query1.exec("insert into student values(0, 'LiMing')");
  query1.exec("insert into student values(1, 'xiaohai')");
  query1.exec("insert into student values(2, 'qiuyu')");

  QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "connection2");
  db2.setDatabaseName("my2.db");
  if (!db2.open()) {
    QMessageBox::critical(0, "Cannot open database2",
                          "Unable to establish a database",
                          QMessageBox::Cancel);
    return -1;
  }

  /// connection
  QSqlQuery query2(db2);
  query2.exec("create table student (id int primary key, name varchar(20))");
  query2.exec("insert into student values(0, 'LIMING')");
  query2.exec("insert into student values(1, 'XIAOHAI')");
  query2.exec("insert into student values(2, 'QIUYU')");

  return true;
}

#endif  // CONNECTION_H
