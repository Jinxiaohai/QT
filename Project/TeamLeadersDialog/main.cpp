#include "teamleadersdialog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QStringList leaders;
  leaders << QString("jin") << QString("xiao") << QString("hai") << QString("wang")
          << QString("xiao") << QString("pang");

  TeamLeadersDialog w(leaders);
  w.show();

  return a.exec();
}
