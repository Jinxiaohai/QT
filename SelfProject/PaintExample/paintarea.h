#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>

class PaintArea : public QWidget {
  Q_OBJECT
 public:
  enum Shape {
    Line,
    Rectangle,
    RoundRect,
    Ellipse,
    Rolygon,
    Polyline,
    Points,
    Arc,
    Path,
    Text,
    Pixmap
  };

  explicit PaintArea(QWidget *parent = nullptr);
  void setShape(Shape s);
  void setPen(QPen p);
  void setBrush(QBrush b);
  void setFillRule(Qt::FillRule rule);
  void paintEvent(QPaintEvent *event);

 signals:

 public slots:

 private:
  Shape shape;
  QPen pen;
  QBrush brush;
  Qt::FillRule fillRule;
};

#endif  // PAINTAREA_H
