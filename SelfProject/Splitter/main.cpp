#include "splitter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Splitter w;
  w.show();

  return a.exec();
}
