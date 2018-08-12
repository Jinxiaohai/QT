#ifndef PIECHART_H
#define PIECHART_H

#include <QChartView>
#include <QPieSeries>
#include <QWidget>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
class QHBoxLayout;
QT_END_NAMESPACE

class PieChart : public QWidget {
  Q_OBJECT
 public:
  explicit PieChart(QWidget *parent = nullptr);

 signals:

 public slots:

 private:
  QChartView *chartView;
  QPieSeries *pieSeries;
  QHBoxLayout *mainLayout;
};

#endif  // PIECHART_H
