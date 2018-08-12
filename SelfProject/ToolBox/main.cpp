#include <QApplication>

#include "drawer.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Drawer drawer;
  drawer.show();

  return app.exec();
}
