#include "widgetaddmenubar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  WidgetAddMenuBar w;
  w.show();

  return a.exec();
}
