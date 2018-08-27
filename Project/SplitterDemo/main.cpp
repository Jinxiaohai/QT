#include "mailsplitter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MailSplitter w;
  w.show();

  return a.exec();
}
