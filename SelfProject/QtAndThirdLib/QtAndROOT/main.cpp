#include "widget.h"
#include <QApplication>
#include "TH1D.h"
#include "TCanvas.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w;
  TCanvas *canvas = new TCanvas("canvas", "canvas", 30, 30, 600, 600);
  TH1D *his = new TH1D("his", "his", 100, -4, 4);
  his->FillRandom("gaus", 10000);
  his->Draw("P");
  canvas->SaveAs("test.eps");
  w.show();

  return a.exec();
}
