#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QSpinBox;
class QDoubleSpinBox;
class QLabel;
class QPushButton;
class QLineEdit;
class QAction;
class QListWidget;
class QGroupBox;
class QGridLayout;
QT_END_NAMESPACE

class TFile;
class TChain;
class Coalescence;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void initROOT();

 public slots:
  void runCoalescence();

 private:
  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();

  void createListWidget();
  void createHelium3Widget();
  void createAntiHelium3Widget();
  void createHypertritonWidget();
  void createAntiHypertritonWidget();
  void createLayout();

  void createOthersWidget();

  void readSettings();
  void writeSettings();
  bool loadFile(const QString &fileName);
  bool saveFile(const QString &fileName);

  QWidget *centralWidget;
  QListWidget *listWidget;

  //
  QWidget *helium3Widget;
  QGroupBox *helium3InformationGroupBox;
  QLabel *helium3MassLabel;
  QLineEdit *helium3MassLineEdit;
  QLabel *helium3pDiffCutLabel;
  QLineEdit *helium3pDiffCutLineEdit;
  QGridLayout *helium3BaseInformationGridLayout;
  QGroupBox *helium3CutGroupBox;
  QLabel *helium3PtLowLabel;
  QDoubleSpinBox *helium3PtLowDoubleSpinBox;
  QLabel *helium3PtHighLabel;
  QDoubleSpinBox *helium3PtHighDoubleSpinBox;
  QLabel *helium3RapidityLowLabel;
  QDoubleSpinBox *helium3RapidityLowDoubleSpinBox;
  QLabel *helium3RapidityHighLabel;
  QDoubleSpinBox *helium3RapidityHighDoubleSpinBox;
  QLabel *helium3CentralityLowLabel;
  QSpinBox *helium3CentralityLowSpinBox;
  QLabel *helium3CentralityHighLabel;
  QSpinBox *helium3CentralityHighSpinBox;
  QGridLayout *helium3CutGridLayout;
  QVBoxLayout *helium3MainLayout;

  //
  QWidget *antiHelium3Widget;
  QGroupBox *antiHelium3InformationGroupBox;
  QLabel *antiHelium3MassLabel;
  QLineEdit *antiHelium3MassLineEdit;
  QLabel *antiHelium3pDiffCutLabel;
  QLineEdit *antiHelium3pDiffCutLineEdit;
  QGridLayout *antiHelium3BaseInformationGridLayout;
  QGroupBox *antiHelium3CutGroupBox;
  QLabel *antiHelium3PtLowLabel;
  QDoubleSpinBox *antiHelium3PtLowDoubleSpinBox;
  QLabel *antiHelium3PtHighLabel;
  QDoubleSpinBox *antiHelium3PtHighDoubleSpinBox;
  QLabel *antiHelium3RapidityLowLabel;
  QDoubleSpinBox *antiHelium3RapidityLowDoubleSpinBox;
  QLabel *antiHelium3RapidityHighLabel;
  QDoubleSpinBox *antiHelium3RapidityHighDoubleSpinBox;
  QLabel *antiHelium3CentralityLowLabel;
  QSpinBox *antiHelium3CentralityLowSpinBox;
  QLabel *antiHelium3CentralityHighLabel;
  QSpinBox *antiHelium3CentralityHighSpinBox;
  QGridLayout *antiHelium3CutGridLayout;
  QVBoxLayout *antiHelium3MainLayout;

  //
  QWidget *hypertritonWidget;
  QGroupBox *hypertritonInformationGroupBox;
  QLabel *hypertritonMassLabel;
  QLineEdit *hypertritonMassLineEdit;
  QLabel *hypertritonpDiffCutLabel;
  QLineEdit *hypertritonpDiffCutLineEdit;
  QGridLayout *hypertritonBaseInformationGridLayout;
  QGroupBox *hypertritonCutGroupBox;
  QLabel *hypertritonPtLowLabel;
  QDoubleSpinBox *hypertritonPtLowDoubleSpinBox;
  QLabel *hypertritonPtHighLabel;
  QDoubleSpinBox *hypertritonPtHighDoubleSpinBox;
  QLabel *hypertritonRapidityLowLabel;
  QDoubleSpinBox *hypertritonRapidityLowDoubleSpinBox;
  QLabel *hypertritonRapidityHighLabel;
  QDoubleSpinBox *hypertritonRapidityHighDoubleSpinBox;
  QLabel *hypertritonCentralityLowLabel;
  QSpinBox *hypertritonCentralityLowSpinBox;
  QLabel *hypertritonCentralityHighLabel;
  QSpinBox *hypertritonCentralityHighSpinBox;
  QGridLayout *hypertritonCutGridLayout;
  QVBoxLayout *hypertritonMainLayout;

  //
  QWidget *antiHypertritonWidget;
  QGroupBox *antiHypertritonInformationGroupBox;
  QLabel *antiHypertritonMassLabel;
  QLineEdit *antiHypertritonMassLineEdit;
  QLabel *antiHypertritonpDiffCutLabel;
  QLineEdit *antiHypertritonpDiffCutLineEdit;
  QGridLayout *antiHypertritonBaseInformationGridLayout;
  QGroupBox *antiHypertritonCutGroupBox;
  QLabel *antiHypertritonPtLowLabel;
  QDoubleSpinBox *antiHypertritonPtLowDoubleSpinBox;
  QLabel *antiHypertritonPtHighLabel;
  QDoubleSpinBox *antiHypertritonPtHighDoubleSpinBox;
  QLabel *antiHypertritonRapidityLowLabel;
  QDoubleSpinBox *antiHypertritonRapidityLowDoubleSpinBox;
  QLabel *antiHypertritonRapidityHighLabel;
  QDoubleSpinBox *antiHypertritonRapidityHighDoubleSpinBox;
  QLabel *antiHypertritonCentralityLowLabel;
  QSpinBox *antiHypertritonCentralityLowSpinBox;
  QLabel *antiHypertritonCentralityHighLabel;
  QSpinBox *antiHypertritonCentralityHighSpinBox;
  QGridLayout *antiHypertritonCutGridLayout;
  QVBoxLayout *antiHypertritonMainLayout;

  QMenu *fileMenu;
  QMenu *helpMenu;

  QToolBar *fileToolBar;
  QToolBar *helpToolBar;

  QAction *newAction;
  QAction *openAction;
  QAction *exitAction;
  QAction *aboutAction;
  QAction *aboutQtAction;

  QLabel *inputFileListLabel;
  QLineEdit *inputFileListLineEdit;
  QLabel *resultFileLabel;
  QLineEdit *resultFileLineEdit;

  QPushButton *okPushButton;
  QPushButton *cancelPushButton;

  TFile *resultFile;
  TChain *chain;

  Coalescence *helium3Coalescence;
  Coalescence *antiHelium3Coalescence;
  Coalescence *hypertritonCoalescence;
  Coalescence *antiHypertritonCoalescence;
};

#endif  // MainWindow_H
