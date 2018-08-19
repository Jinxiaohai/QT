#include <QApplication>

#include "layout.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  Layout absoluteLayout;
  absoluteLayout.show();

  return app.exec();
}
