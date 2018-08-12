#include <standarddialog.h>
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  StandardDialog standardDialog;
  standardDialog.show();

  return a.exec();
}
