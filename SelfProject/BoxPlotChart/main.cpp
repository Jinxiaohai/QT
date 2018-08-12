#include <QApplication>
#include <QBarCategoryAxis>
#include <QBoxPlotSeries>
#include <QBoxSet>
#include <QChartView>
#include <QFile>
#include <QLegend>
#include <QMainWindow>

#include "boxdatareader.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QBoxPlotSeries *acmeSeries = new QBoxPlotSeries();
  acmeSeries->setName("Ace Ltd");

  QBoxPlotSeries *boxWhiskSeries = new QBoxPlotSeries();
  boxWhiskSeries->setName("BoxWhisk Inc");

  QFile acmeData(":acme_data.txt");
  if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return -1;
  }

  BoxDataReader dataReader(&acmeData);
  while (!dataReader.atEnd()) {
    QBoxSet *set = dataReader.readBox();
    if (set) {
      acmeSeries->append(set);
    }
  }

  QFile boxwhiskData(":boxwhisk_data.txt");
  if (!boxwhiskData.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return -1;
  }

  dataReader.readFile(&boxwhiskData);
  while (!dataReader.atEnd()) {
    QBoxSet *set = dataReader.readBox();
    if (set) {
      boxWhiskSeries->append(set);
    }
  }

  QChart *chart = new QChart();
  chart->addSeries(acmeSeries);
  chart->addSeries(boxWhiskSeries);
  chart->setTitle("xiaohai chart example.");
  chart->setAnimationOptions(QChart::SeriesAnimations);

  chart->createDefaultAxes();
  chart->axisY()->setMin(15.0);
  chart->axisY()->setMax(34.0);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QMainWindow window;
  window.setCentralWidget(chartView);
  window.resize(800, 600);
  window.show();

  return a.exec();
}
