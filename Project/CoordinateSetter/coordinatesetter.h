#ifndef COORDINATESETTER_H
#define COORDINATESETTER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QTableWidget;
QT_END_NAMESPACE

class CoordinateSetter : public QDialog {
  Q_OBJECT

 public:
  CoordinateSetter(QList<QPointF> *coords, QWidget *parent = 0);
  ~CoordinateSetter();

  void done(int result);

 private
slots:
  void addRow();

 private:
  QDialogButtonBox *buttonBox;
  QTableWidget *tableWidget;
  QList<QPointF> *coordinates;
};

#endif  // COORDINATESETTER_H
