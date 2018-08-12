#include <QBitmap>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

#include "shapewidget.h"

ShapeWidget::ShapeWidget(QWidget *parent) : QMainWindow(parent) {
  QPixmap pix;
  pix.load(":/background.jpg", 0,
           Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
  this->resize(pix.size());
  this->setMask(QBitmap(pix.mask()));
}

ShapeWidget::~ShapeWidget() {}

void ShapeWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
  }
  if (event->button() == Qt::RightButton) {
    close();
  }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event) {
  if (event->button() & Qt::LeftButton) {
    this->move(event->globalPos() - dragPosition);
    event->accept();
  }
}

void ShapeWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, QPixmap(":/images/background.jpg"));
}
