#include <QApplication>
#include "paomadeng.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  PaoMaDeng w;
  w.setWindowTitle(QObject::tr("Pao Ma Deng"));
  w.setText(QObject::tr("I am xiaohai, ....."));
  w.show();

  return a.exec();
}
