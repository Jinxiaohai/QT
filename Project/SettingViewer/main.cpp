#include "settingviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SettingViewer w;
  w.show();

  return a.exec();
}
