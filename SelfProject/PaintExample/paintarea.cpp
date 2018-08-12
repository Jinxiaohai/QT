#include <QPainter>

#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent) {
  this->setPalette(QPalette(Qt::white));
  this->setAutoFillBackground(true);
  this->setMinimumSize(400, 400);
}

void PaintArea::setShape(PaintArea::Shape s) {
  shape = s;
  this->update();
}

void PaintArea::setPen(QPen p) {
  pen = p;
  this->update();
}

void PaintArea::setBrush(QBrush b) {
  brush = b;
  this->update();
}

void PaintArea::setFillRule(Qt::FillRule rule) {
  fillRule = rule;
  this->update();
}

void PaintArea::paintEvent(QPaintEvent *event) {
  QPainter p(this);
  p.setPen(pen);
  p.setBrush(brush);

  QRect rect(50, 100, 300, 200);
  static const QPoint points[4] = {QPoint(150, 100), QPoint(300, 150),
                                   QPoint(350, 250), QPoint(100, 300)};
}
