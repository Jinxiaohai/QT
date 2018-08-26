#include <QApplication>
#include <QSplitter>
#include <QTextEdit>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QTextEdit *editor1 = new QTextEdit;
  QTextEdit *editor2 = new QTextEdit;
  QTextEdit *editor3 = new QTextEdit;

  QSplitter splitter(Qt::Horizontal);
  splitter.addWidget(editor1);
  splitter.addWidget(editor2);
  splitter.addWidget(editor3);

  editor1->setPlainText("天堂有路你不走");
  editor2->setPlainText("地狱无门你闯进来");
  editor3->setPlainText("哈哈哈");

  splitter.show();
  return app.exec();
}
