#ifndef ICONEDITOR_H
#define ICONEDITOR_H

#include <QColor>
#include <QImage>
#include <QWidget>

class IconEditor : public QWidget {
  Q_OBJECT

  Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
  Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
  Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

 public:
  IconEditor(QWidget *parent = 0);
  ~IconEditor();

  QColor penColor() const;
  void setPenColor(const QColor &newColor);

  int zoomFactor() const;
  void setZoomFactor(int newZoom);

  QImage iconImage() const;
  void setIconImage(const QImage &newImage);

  QSize sizeHint() const;

 protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void paintEvent(QPaintEvent *event);

 private:
  void setImagePixel(const QPoint &pos, bool opaque);
  QRect pixelRect(int i, int j) const;

  QColor curColor;
  QImage image;
  int zoom;
};

#endif  // ICONEDITOR_H
