#ifndef DIGICLOCK_H
#define DIGICLOCK_H

#include <QLCDNumber>

class DigiClock : public QLCDNumber {
 public:
  DigiClock();

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *events);

 public slots:
  void showTime();

 private:
  QPoint dragPosition;
  bool showColon;
};

#endif  // DIGICLOCK_H
