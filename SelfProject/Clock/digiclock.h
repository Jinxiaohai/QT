#ifndef DIGICLOCK_H
#define DIGICLOCK_H

#include <QLCDNumber>

QT_BEGIN_NAMESPACE
class QPoint;
class QMouseEvent;
QT_END_NAMESPACE

class DigiClock : public QLCDNumber {
  Q_OBJECT

 public:
  explicit DigiClock(QWidget *parent = nullptr);

 protected:
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);

 public slots:
  void showTime();

 private:
  QPoint dragPosition;
  bool showColon;
};

#endif  // DIGICLOCK_H
