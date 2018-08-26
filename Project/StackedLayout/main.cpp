#include "stackedlayout.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  StackedLayout w;
  w.show();

  return a.exec();
}
