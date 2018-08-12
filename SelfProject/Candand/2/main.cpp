#include <QtCore/qglobal.h>
#include <QDebug>
#include <QtCore/QCoreApplication>

/// @brief 该函数的主函数
///
/// @param argc 参数的个数
/// @param argv 参数的字符指针
///
/// @return a.exec()
///
int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QString testStringName = "hello world";
  qDebug() << testStringName;

  return a.exec();
}
