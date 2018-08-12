#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QWidget *window = new QWidget;
  window->setWindowTitle("xiaohai test");

  QGridLayout *layout = new QGridLayout;

  QLabel *label1 = new QLabel("Name:");
  QLineEdit *textLineEdit = new QLineEdit;

  QLabel *label2 = new QLabel("Name:");
  QLineEdit *textLineEdit2 = new QLineEdit;

  QPushButton *button = new QPushButton("Ok");

  layout->addWidget(label1, 0, 0);
  layout->addWidget(textLineEdit, 0, 1);
  layout->addWidget(label2, 1, 0);
  layout->addWidget(textLineEdit2, 1, 1);
  layout->addWidget(button, 2, 0, 1, 2);

  window->setLayout(layout);
  window->show();
  return app.exec();
}
