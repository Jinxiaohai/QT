#include <QApplication>
#include "piechart.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  PieChart pieChart;
  pieChart.show();

  return app.exec();
}
