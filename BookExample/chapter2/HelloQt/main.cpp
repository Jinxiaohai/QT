#include <QApplication>
#include <QtWidgets>

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  QFile file(":/qss/myqss.qss");
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "OPEN ERROR";
  }
  QString styleSheet = QString(file.readAll());

  QDialog w;
  w.setStyleSheet(styleSheet);
  w.resize(400, 300);
  QLabel label(&w);
  label.setText(QObject::tr("Hello Qt"));
  label.move(200, 150);
  w.show();

  return app.exec();
}
