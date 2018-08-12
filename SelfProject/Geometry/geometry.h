#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QGridLayout;
QT_END_NAMESPACE

class Geometry : public QDialog {
  Q_OBJECT

 public:
  Geometry(QWidget *parent = 0);
  ~Geometry();
  void updateLabel();

 protected:
  void moveEvent(QMoveEvent *event);
  void resizeEvent(QResizeEvent *event);

 private:
  QLabel *xLabel;
  QLabel *xValueLabel;

  QLabel *yLabel;
  QLabel *yValueLabel;

  QLabel *FrmLabel;
  QLabel *FrmValueLabel;

  QLabel *posLabel;
  QLabel *posValueLabel;

  QLabel *geoLabel;
  QLabel *geoValueLabel;

  QLabel *widthLabel;
  QLabel *widthValueLabel;

  QLabel *heightLabel;
  QLabel *heightValueLabel;

  QLabel *rectLabel;
  QLabel *rectValueLabel;

  QLabel *sizeLabel;
  QLabel *sizeValueLabel;

  QGridLayout *mainLayout;
};

#endif  // GEOMETRY_H
