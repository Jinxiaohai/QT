#include "clock.h"

Clock::Clock(QWidget *parent) : QFrame(parent) {
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(1000);
  setWindowTitle(tr("Xiaohai Clock"));
  setFixedSize(200, 200);
  setFrameShape(QFrame::Box);
  setFrameShadow(QFrame::Plain);
  setStyleSheet(getQss());
}

void Clock::paintEvent(QPaintEvent *event) {
  static const QPointF hourHand[3] = {QPointF(7, 8), QPointF(-7, 8),
                                      QPointF(0, -40)};
  static const QPointF minuteHand[3] = {QPointF(7, 8), QPointF(-7, 8),
                                        QPointF(0, -70)};
  QColor hourColor(127, 0, 127);
  QColor minuteColor(0, 127, 127, 191);

  int side = qMin(width(), height());
  QTime time = QTime::currentTime();

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(width() / 2, height() / 2);
  painter.scale(side / 200.0, side / 200.0);

  painter.setPen(Qt::NoPen);
  painter.setBrush(hourColor);
  painter.save();
  painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
  painter.drawConvexPolygon(hourHand, 3);
  painter.restore();

  painter.setPen(hourColor);

  for (int i = 0; i != 12; ++i) {
    painter.drawLine(88, 0, 96, 0);
    painter.rotate(30.0);
  }

  painter.setPen(Qt::NoPen);
  painter.setBrush(minuteColor);

  painter.save();
  painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
  painter.drawConvexPolygon(minuteHand, 3);

  painter.setPen(minuteColor);

  for (int i = 0; i != 60; ++i) {
    if ((i % 5 != 0)) {
      painter.drawLine(92, 0, 96, 0);
    }
    painter.rotate(6.0);
  }
}

const QString Clock::getQss() const {
  QFile file(":/qss/myqss.qss");
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "open error.";
  }
  QString myqss = QString(file.readAll());
  file.close();
  return myqss;
}
