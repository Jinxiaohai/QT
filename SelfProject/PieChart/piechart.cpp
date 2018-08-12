#include <QHBoxLayout>

#include "piechart.h"

PieChart::PieChart(QWidget *parent) : QWidget(parent) {
  pieSeries = new QPieSeries;
  pieSeries->append("10%", 1);
  pieSeries->append("20%", 2);
  pieSeries->append("70%", 7);
  pieSeries->setLabelsVisible(true);

  //  QPieSlice *sliceRed = pieSeries->slices().at(0);
  //  sliceRed->setColor(QColor(255, 0, 0, 255));
  //  QPieSlice *sliceGreen = pieSeries->slices().at(1);
  //  sliceGreen->setColor(QColor(0, 255, 0, 255));
  //  QPieSlice *sliceBlue = pieSeries->slices().at(2);
  //  sliceBlue->setColor(QColor(0, 0, 255, 255));

  QChart *chart = new QChart;
  chart->addSeries(pieSeries);
  chart->setTitle("Pie Chart Example");
  chart->legend()->hide();

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(chartView);

  this->setFixedSize(600, 600);
}
