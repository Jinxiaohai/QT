#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QLabel *label = new QLabel("<h2>hello</h2> <font color=red><b>Qt</b>");
  label->show();

  return a.exec();
}
