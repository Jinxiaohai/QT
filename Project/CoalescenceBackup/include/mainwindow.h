#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TH1D;
class TFile;
class AMPT;
class TChain;
class Track;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  enum PARTICLETYPE { Helium3 = 0, AntiHelium3 = 1, Hypertriton = 2, AntiHypertriton = 3 };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void setDefaultParameters();
  void setHistograms();
  void loadData();
  void readInBuffer(AMPT *&ampt);
  void loopEvent();
  void writeData();

  void coalescence(PARTICLETYPE type);

 protected:
  void changeEvent(QEvent *e);

 private slots:
  void isGenerateHelium3(int checkBoxState);
  void isGenerateAntiHelium3(int checkBoxState);
  void isGenerateHypertriton(int checkBoxState);
  void isGenerateAntiHypertriton(int checkBoxState);

  void run();

 private:
  void coalescenceHelium3();
  void coalescenceAntiHelium3();
  void coalescenceHypertriton();
  void coalescenceAntiHypertriton();

  Ui::MainWindow *ui;

  TChain *chain;

  QVector<Track> protonTracks;
  QVector<Track> antiProtonTracks;
  QVector<Track> neutronTracks;
  QVector<Track> antiNeutronTracks;
  QVector<Track> lambdaTracks;
  QVector<Track> antiLambdaTracks;

  TH1D *helium3dNdy;
  TH1D *helium3dNdydPt;
  TH1D *antiHelium3dNdy;
  TH1D *antiHelium3dNdydPt;
  TH1D *hypertritondNdy;
  TH1D *hypertritondNdydPt;
  TH1D *antiHypertritondNdy;
  TH1D *antiHypertritondNdydPt;

  TFile *resultFile;
};

#endif  // MAINWINDOW_H
