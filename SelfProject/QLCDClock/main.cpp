#include "qlcddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QLCDDialog w;
  w.show();

  return a.exec();
}
