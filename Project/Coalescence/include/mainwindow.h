#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TH1D;
class AMPT;
class TChain;
class Coalescence;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void settingDefaultParameters();
  void initHistogram();
  void loadData();
  void writeData();

 protected:
  void changeEvent(QEvent *e);

 private slots:
  void isGenerateHelium3(int checkBoxState);
  void isGenerateAntiHelium3(int checkBoxState);
  void isGenerateHypertriton(int checkBoxState);
  void isGenerateAntiHypertriton(int checkBoxState);

  void run();

 private:
  Ui::MainWindow *ui;

  AMPT *ampt;
  TChain *chain;
  Coalescence *coalescence;
};

#endif  // MAINWINDOW_H
