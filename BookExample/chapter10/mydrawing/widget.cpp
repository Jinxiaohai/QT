#include "widget.h"
#include "ui_widget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() { delete ui; }

void Widget::changeEvent(QEvent *e) {
  QWidget::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void Widget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawLine(QPoint(0, 0), QPoint(100, 100));

  QPen pen(Qt::green, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
  painter.setPen(pen);
  QRectF rectangle(70, 40, 80, 60);
  int startAngle = 30 * 16;
  int spanAngle = 160 * 16;
  painter.drawArc(rectangle, startAngle, spanAngle);

  pen.setWidth(1);
  pen.setStyle(Qt::SolidLine);
  painter.setPen(pen);

  painter.drawRect(160, 20, 50, 40);
  QBrush brush(QColor(0, 0, 255), Qt::SolidPattern);
  painter.setBrush(brush);
  painter.drawEllipse(220, 20, 50, 50);
  brush.setTexture(QPixmap("./panda.png"));
  painter.setBrush(brush);

  static const QPointF points[4] = {QPointF(270.0, 80.0), QPointF(290.0, 10.0),
                                    QPointF(350.0, 30.0), QPointF(390.0, 70.0)};
  painter.drawPolygon(points, 4);

  painter.fillRect(QRect(10, 100, 150, 20), QBrush(Qt::darkYellow));
  painter.eraseRect(QRect(50, 0, 50, 120));

  QLinearGradient lineGradient(QPointF(40, 190), QPointF(10, 190));
  lineGradient.setColorAt(0, Qt::yellow);
  lineGradient.setColorAt(0.5, Qt::red);
  lineGradient.setColorAt(1, Qt::green);
  lineGradient.setSpread(QGradient::RepeatSpread);
  painter.setBrush(lineGradient);
  painter.drawRect(10, 170, 90, 40);

  QRadialGradient radialGradient(QPointF(200, 190), 50, QPointF(275, 200));
  radialGradient.setColorAt(0, QColor(255, 255, 100, 150));
  radialGradient.setColorAt(1, QColor(0, 0, 0, 50));
  painter.setBrush(radialGradient);
  painter.drawEllipse(QPointF(200, 190), 50, 50);

  QConicalGradient conicalGradient(QPointF(350, 190), 60);
  conicalGradient.setColorAt(0.2, Qt::cyan);
  conicalGradient.setColorAt(0.9, Qt::black);
  painter.setBrush(conicalGradient);
  painter.drawEllipse(QPointF(350, 190), 50, 50);

  painter.setPen(QPen(lineGradient, 2));
  painter.drawLine(0, 280, 100, 280);
  painter.drawText(150, 200, tr("hello HIRG."));
}
