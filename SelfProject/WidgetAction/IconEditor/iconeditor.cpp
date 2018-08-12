#include <QKeyEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

#include "iconeditor.h"

IconEditor::IconEditor(QWidget *parent) : QWidget(parent) {
  this->setAttribute(Qt::WA_StaticContents);
  this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  this->curColor = Qt::black;
  this->zoom = 8;

  this->image = QImage(16, 16, QImage::Format_ARGB32);
  image.fill(qRgba(0, 0, 0, 0));
}

IconEditor::~IconEditor() {}

QColor IconEditor::penColor() const { return this->penColor(); }

void IconEditor::setPenColor(const QColor &newColor) {
  this->curColor = newColor;
}

int IconEditor::zoomFactor() const { return this->zoom; }

void IconEditor::setZoomFactor(int newZoom) {
  if (newZoom < 1) {
    zoom = 1;
  }
  if (newZoom != zoom) {
    zoom = newZoom;
    this->update();
    this->updateGeometry();
  }
}

QImage IconEditor::iconImage() const { return this->image; }

void IconEditor::setIconImage(const QImage &newImage) {
  if (newImage != image) {
    this->image = newImage.convertToFormat(QImage::Format_ARGB32);
    this->update();
    this->updateGeometry();
  }
}

QSize IconEditor::sizeHint() const {
  QSize size = zoom * image.size();
  if (zoom >= 3) {
    size += QSize(1, 1);
  }
  return size;
}

void IconEditor::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    setImagePixel(event->pos(), true);
  } else if (event->button() == Qt::RightButton) {
    setImagePixel(event->pos(), false);
  }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
    setImagePixel(event->pos(), true);
  } else if (event->button() & Qt::RightButton) {
    setImagePixel(event->pos(), false);
  }
}

void IconEditor::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  if (zoom >= 3) {
    painter.setPen(palette().foreground().color());
    for (int i = 0; i <= image.width(); ++i) {
      painter.drawLine(zoom * i, 0, zoom * i, zoom * image.height());
    }
    for (int j = 0; j <= image.height(); ++j) {
      painter.drawLine(0, zoom * j, zoom * image.width(), zoom * j);
    }
  }

  for (int i = 0; i < image.width(); ++i) {
    for (int j = 0; j < image.height(); ++j) {
      QRect rect = pixelRect(i, j);
      if (!event->region().intersect(rect).isEmpty()) {
        QColor color = QColor::fromRgba(image.pixel(i, j));
        if (color.alpha() < 255) {
          painter.fillRect(rect, Qt::white);
        }
        painter.fillRect(rect, color);
      }
    }
  }
}

void IconEditor::setImagePixel(const QPoint &pos, bool opaque) {
  int i = pos.x() / zoom;
  int j = pos.y() / zoom;

  if (image.rect().contains(i, j)) {
    if (opaque) {
      image.setPixel(i, j, penColor().rgba());
    } else {
      image.setPixel(i, j, qRgba(0, 0, 0, 0));
    }

    this->update(pixelRect(i, j));
  }
}

QRect IconEditor::pixelRect(int i, int j) const {
  if (zoom >= 3) {
    return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
  } else {
    return QRect(zoom * i, zoom * j, zoom, zoom);
  }
}
