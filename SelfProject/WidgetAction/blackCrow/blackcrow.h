#ifndef BLACKCROW_H
#define BLACKCROW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QWidget;
QT_END_NAMESPACE

class BlackCrow : public QWidget {
  Q_OBJECT

 public:
  BlackCrow(QWidget *parent = 0);
  ~BlackCrow();

 private:
  QWidget *firstLine[4];
  QWidget *secondLine[4];
  QWidget *thirdLine[4];
};

#endif  // BLACKCROW_H
