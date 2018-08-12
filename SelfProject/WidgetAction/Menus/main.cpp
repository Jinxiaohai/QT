#include <QApplication>
#include "Menus.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Menus w;
  w.show();

  return a.exec();
}
