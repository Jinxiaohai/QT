#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QPoint>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

class PaintArea : public QWidget {
  Q_OBJECT
 public:
  enum ShapeType { None = 0, Line = 1, Rectangle = 2, Ellipse = 3 };

  explicit PaintArea(QWidget *parent = nullptr);

  QSize getImageSize();
  void setImageSize(int width, int height);
  void setImageColor(QColor color);

  bool isModified() const;
  bool saveImage(const QString &fileName, const char *fileFormat);
  bool openImage(const QString &fileName);

  void doPrint();

  void zoomIn();
  void zoomOut();
  void zoom_1();
  void doRotate();
  void doShear();
  void doClear();

  void setPenStyle(Qt::PenStyle style);
  void setPenWidth(int width);
  void setPenColor(QColor color);
  void setBrushColor(QColor color);

  void setShape(ShapeType shape);

 protected:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

 private:
  QImage image;
  QRgb backColor;

  QPoint lastPoint;
  QPoint endPoint;

  bool modified;

  void paint(QImage &theImage);

  qreal scale;
  qint64 angle;
  qreal shear;

  QColor penColor;
  QColor brushColor;
  int penWidth;
  Qt::PenStyle penStyle;

  ShapeType curShape;

 signals:

 public slots:
};

#endif  // PAINTAREA_H
