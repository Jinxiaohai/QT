#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QWidget *window = new QWidget;

  window->setWindowTitle("Hello Qt");

  QPushButton *button1 = new QPushButton("first");
  QPushButton *button2 = new QPushButton("second");
  QPushButton *button3 = new QPushButton("third");

  // QHBoxLayout *hlayout = new QHBoxLayout;
  QVBoxLayout *vlayout = new QVBoxLayout;
  vlayout->addWidget(button1);
  vlayout->addWidget(button2);
  vlayout->addWidget(button3);

  window->setLayout(vlayout);

  window->show();
  return app.exec();
}
