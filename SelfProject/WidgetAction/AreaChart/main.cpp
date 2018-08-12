#include <QApplication>
#include <QAreaSeries>
#include <QChartView>
#include <QLineSeries>
#include <QMainWindow>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QLineSeries *series0 = new QLineSeries();
  QLineSeries *series1 = new QLineSeries();

  (*series0) << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7)
             << QPointF(12, 6) << QPointF(16, 7) << QPointF(18, 5);
  (*series1) << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2)
             << QPointF(12, 3) << QPointF(16, 4) << QPointF(18, 3);

  QAreaSeries *series = new QAreaSeries(series0, series1);
  series->setName("area chart");
  QPen pen(0x059605);
  pen.setWidth(3);
  series->setPen(pen);

  QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
  gradient.setColorAt(0.0, 0x3cc62c);
  gradient.setColorAt(1.0, 0x26f626);
  gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
  series->setBrush(gradient);

  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Area chart");
  chart->createDefaultAxes();
  chart->axisX()->setRange(0, 20);
  chart->axisY()->setRange(0, 10);
  chart->axisX()->setTitleText("I am X title");

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QMainWindow window;
  window.setCentralWidget(chartView);
  window.resize(400, 300);
  window.show();

  return app.exec();
}
