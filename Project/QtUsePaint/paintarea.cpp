#include <QMouseEvent>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent) {
  image = QImage(400, 300, QImage::Format_RGB32);
  backColor = qRgb(255, 255, 255);
  image.fill(backColor);

  modified = false;

  scale = 1;
  angle = 0;
  shear = 0;

  penColor = Qt::black;
  brushColor = Qt::black;
  penWidth = 1;
  penStyle = Qt::SolidLine;
  curShape = None;
}

QSize PaintArea::getImageSize() { return image.size(); }

void PaintArea::setImageSize(int width, int height) {
  QImage newImage(width, height, QImage::Format_RGB32);
  image = newImage;
  update();
}

void PaintArea::setImageColor(QColor color) {
  backColor = color.rgb();
  image.fill(backColor);
  update();
}

bool PaintArea::isModified() const { return modified; }

bool PaintArea::saveImage(const QString &fileName, const char *fileFormat) {
  QImage visibleImage = image;

  if (visibleImage.save(fileName, fileFormat)) {
    modified = false;
    return true;
  } else {
    return false;
  }
}

bool PaintArea::openImage(const QString &fileName) {
  QImage loadedImage;
  if (!loadedImage.load(fileName)) {
    return false;
  }

  QSize newSize = loadedImage.size();
  setImageSize(newSize.width(), newSize.height());
  image = loadedImage;

  modified = true;
  update();
  return true;
}

void PaintArea::doPrint() {
  QPrinter printer(QPrinter::HighResolution);

  QPrintDialog *printDialog = new QPrintDialog(&printer, this);
  if (printDialog->exec() == QDialog::Accepted) {
    QPainter painter(&printer);
    QRect rect = painter.viewport();
    QSize size = image.size();
    size.scale(rect.size(), Qt::KeepAspectRatio);
    painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
    painter.setWindow(image.rect());
    painter.drawImage(0, 0, image);
  }
}

void PaintArea::zoomIn() {
  scale *= 1.2;
  update();
}

void PaintArea::zoomOut() {
  scale /= 1.2;
  update();
}

void PaintArea::zoom_1() {
  scale = 1;
  update();
}

void PaintArea::doRotate() {
  angle += 90;
  update();
}

void PaintArea::doShear() {
  shear = 0.2;
  update();
}

void PaintArea::doClear() {
  image.fill(backColor);
  update();
}

void PaintArea::setPenStyle(Qt::PenStyle style) { penStyle = style; }

void PaintArea::setPenWidth(int width) { penWidth = width; }

void PaintArea::setPenColor(QColor color) { penColor = color; }

void PaintArea::setBrushColor(QColor color) { brushColor = color; }

void PaintArea::setShape(PaintArea::ShapeType shape) { curShape = shape; }

void PaintArea::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);

  painter.scale(scale, scale);
  if (angle) {
    QPointF center(image.width() / 2.0, image.height() / 2.0);
    painter.translate(center);
    painter.rotate(angle);
    painter.translate(-center);
  }
  if (shear) {
    painter.shear(shear, shear);
  }

  painter.drawImage(0, 0, image);
}

void PaintArea::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    lastPoint = event->pos();
  }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
    endPoint = event->pos();
    paint(image);
  }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    endPoint = event->pos();
    paint(image);
  }
}

void PaintArea::paint(QImage &theImage) {
  QPainter pp(&theImage);
  QPen pen = QPen();
  pen.setColor(penColor);
  pen.setStyle(penStyle);
  pen.setWidth(penWidth);
  QBrush brush = QBrush(brushColor);
  pp.setPen(pen);
  pp.setBrush(brush);

  int x, y, w, h;
  x = lastPoint.x();
  y = lastPoint.y();
  w = endPoint.x() - x;
  h = endPoint.y() - y;

  switch (curShape) {
    case None: {
      pp.drawLine(lastPoint, endPoint);
      lastPoint = endPoint;
      break;
    }
    case Line: {
      pp.drawLine(lastPoint, endPoint);
      break;
    }
    case Rectangle: {
      pp.drawRect(x, y, w, h);
      break;
    }
    case Ellipse: {
      pp.drawEllipse(x, y, w, h);
      break;
    }
  }

  update();

  modified = true;
}
