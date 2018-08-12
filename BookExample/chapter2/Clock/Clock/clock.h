#ifndef CLOCK_H
#define CLOCK_H

#include <QtWidgets>

class Clock : public QFrame {
  Q_OBJECT
 public:
  Clock(QWidget *parent = 0);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  const QString getQss() const;
};

#endif  // CLOCK_H
