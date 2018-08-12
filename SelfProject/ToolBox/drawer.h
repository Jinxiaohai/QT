#ifndef DRAWER_H
#define DRAWER_H

#include <QToolBox>

QT_BEGIN_NAMESPACE
class QToolButton;
QT_END_NAMESPACE

class Drawer : public QToolBox {
 public:
  explicit Drawer(QWidget *parent = nullptr, Qt::WindowFlags f = 0);

 private:
  QToolButton *toolBtn1_1;
  QToolButton *toolBtn1_2;
  QToolButton *toolBtn1_3;
  QToolButton *toolBtn1_4;
  QToolButton *toolBtn1_5;

  QToolButton *toolBtn2_1;
  QToolButton *toolBtn2_2;

  QToolButton *toolBtn3_1;
  QToolButton *toolBtn3_2;
};

#endif  // DRAWER_H
