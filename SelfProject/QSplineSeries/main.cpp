#include <QApplication>
#include <QChartView>
#include <QMainWindow>
#include <QPointF>
#include <QSplineSeries>

#include "QssStyle.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QssStyle::setStyle(":/myqss.qss");
  QSplineSeries *series = new QSplineSeries();
  series->setName("spline");

  series->append(0, 6);
  series->append(2, 4);
  series->append(3, 8);
  series->append(7, 4);
  series->append(10, 5);
  series->append(11, 1);
  series->append(13, 3);
  series->append(17, 6);
  series->append(18, 3);
  series->append(20, 2);

  QChart *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(series);
  chart->setTitle("Simple spline chart example");
  chart->createDefaultAxes();
  chart->axisY()->setRange(0, 10);

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QMainWindow window;
  window.setCentralWidget(chartView);
  window.resize(400, 300);
  window.show();

  return app.exec();
}
