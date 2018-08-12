#include "blackcrow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  BlackCrow w;
  w.show();

  return a.exec();
}
