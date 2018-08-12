#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QtAlgorithms>
#include <QtMath>

#include "Line.h"
#include "ui_Line.h"

using namespace QtCharts;

Line::Line(QWidget *parent) : QMainWindow(parent), ui(new Ui::Line) {
  ui->setupUi(this);
  createChart();
}

Line::~Line() { delete ui; }

void Line::changeEvent(QEvent *e) {
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void Line::createChart() {
  QChartView *chartView = new QChartView(this);
  QChart *chart = new QChart();
  chart->setTitle("A simple line");
  chartView->setChart(chart);
  this->setCentralWidget(chartView);

  QLineSeries *series0 = new QLineSeries();
  QLineSeries *series1 = new QLineSeries();
  series0->setName("Sin");
  series1->setName("Cos");
  chart->addSeries(series0);
  chart->addSeries(series1);

  double t = 0., y1 = 0., y2 = 0., intv = 0.1;
  int cnt = 100;
  for (int i = 0; i != cnt; ++i) {
    y1 = qSin(t);
    series0->append(t, y1);
    y2 = qSin(t + 20);
    series1->append(t, y2);
    t += intv;
  }

  QValueAxis *axisX = new QValueAxis();
  axisX->setRange(0, 10);
  axisX->setTitleText("time(secs");

  QValueAxis *axisY = new QValueAxis();
  axisY->setRange(-2, 2);
  axisY->setTitleText("value");

  chart->setAxisX(axisX, series0);
  chart->setAxisY(axisY, series0);
  chart->setAxisX(axisX, series1);
  chart->setAxisY(axisY, series1);
}
