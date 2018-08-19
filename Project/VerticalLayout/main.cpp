#include <QApplication>
#include "verticallayout.h"

int main(int argc, char **argv) {
  QApplication a(argc, argv);

  VerticalLayout window;
  window.show();

  return a.exec();
}
