#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDebug>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QGraphicsScene scene;
  QGraphicsEllipseItem *item = new QGraphicsEllipseItem(0, 0, 100, 100);
  scene.addItem(item);
  QGraphicsView view(&scene);
  view.setForegroundBrush(QColor(255, 255, 0, 100));
  view.setBackgroundBrush(QPixmap("../test.png"));
  view.resize(400, 300);
  view.show();

  return app.exec();
}
