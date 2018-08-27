#include <iostream>

#include <QAction>
#include <QDir>
#include <QDoubleSpinBox>
#include <QFile>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenuBar>
#include <QPushButton>
#include <QStackedLayout>
#include <QTextStream>
#include <QToolBar>

#include "TChain.h"
#include "TFile.h"

#include "coalescence.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  createActions();
  createMenus();
  createToolBars();
  createStatusBar();

  createHelium3Widget();
  createAntiHelium3Widget();
  createHypertritonWidget();
  createAntiHypertritonWidget();

  createListWidget();
  createOthersWidget();

  createLayout();

  this->setWindowTitle(tr("利用Navie组合模型来生成氦3、超氚核以及相应的反粒子"));
}

MainWindow::~MainWindow() {
  // delete resultFile;
  // delete chain;
}

void MainWindow::initROOT() {
  // resultFile = new TFile(resultFileLineEdit->text().toStdString().c_str(), "RECREATE");

  QString inputFileList = this->inputFileListLineEdit->text();
  QFile file(inputFileList);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    std::cout << "Can not open file for reading: " << qPrintable(file.errorString()) << std::endl;
  }

  chain = new TChain("AMPT");
  QTextStream in(&file);
  while (!in.atEnd()) {
    QString eachRootFile = in.readLine();
    TFile *testRootFile = new TFile(eachRootFile.toStdString().c_str());
    if (!testRootFile || !testRootFile->IsOpen() || !testRootFile->GetNkeys()) {
      std::cout << "The root file is bad :" << qPrintable(eachRootFile) << std::endl;
    } else {
      chain->Add(eachRootFile.toStdString().c_str());
    }
    delete testRootFile;
  }
  file.close();
}

void MainWindow::runCoalescence() { initROOT(); }

void MainWindow::createActions() {
  newAction = new QAction(tr("新建"), this);
  newAction->setIcon(QIcon(":/images/new.png"));
  newAction->setShortcut(QKeySequence::New);
  newAction->setStatusTip(tr("新建一个文件"));
  // link signal and slot

  openAction = new QAction(tr("打开"), this);
  openAction->setIcon(QIcon(":/images/open.png"));
  openAction->setShortcut(QKeySequence::Open);
  openAction->setStatusTip(tr("打开一个文件"));
  // link signal and slot

  exitAction = new QAction(tr("退出"), this);
  exitAction->setIcon(QIcon(":/images/exit.png"));
  exitAction->setShortcut(QKeySequence::Quit);
  exitAction->setStatusTip(tr("退出程序"));
  // link signal and slot

  aboutAction = new QAction(tr("关于"), this);
  aboutAction->setIcon(QIcon(":/images/aboutQt.png"));
  aboutAction->setStatusTip(tr("该程序用来完成氦3、超氚核以及反粒子的生成"));
  // link signal and slot

  aboutQtAction = new QAction(tr("关于Qt"), this);
  aboutQtAction->setIcon(QIcon(":/images/aboutQt.png"));
  aboutQtAction->setStatusTip(tr("关于Qt"));
  // link signal and slot
}

void MainWindow::createMenus() {
  fileMenu = this->menuBar()->addMenu(tr("文件"));
  fileMenu->addAction(newAction);
  fileMenu->addAction(openAction);
  fileMenu->addAction(exitAction);

  helpMenu = this->menuBar()->addMenu(tr("帮助"));
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars() {
  fileToolBar = this->addToolBar(tr("&File"));
  fileToolBar->addAction(newAction);
  fileToolBar->addAction(openAction);
  fileToolBar->addAction(exitAction);

  helpToolBar = this->addToolBar(tr("&Help"));
  helpToolBar->addAction(aboutAction);
  helpToolBar->addAction(aboutQtAction);
}

void MainWindow::createStatusBar() {}

void MainWindow::createListWidget() {
  listWidget = new QListWidget(this);
  listWidget->addItem(tr("氦3"));
  listWidget->addItem(tr("反氦3"));
  listWidget->addItem(tr("超氚核"));
  listWidget->addItem(tr("反超氚核"));
}

void MainWindow::createHelium3Widget() {
  helium3Widget = new QWidget(this);

  helium3Coalescence = new Coalescence(helium3Widget);

  helium3InformationGroupBox = new QGroupBox(tr("是否想生成氦3"));
  helium3InformationGroupBox->setCheckable(true);
  helium3InformationGroupBox->setChecked(false);

  helium3MassLabel = new QLabel(tr("核质量(GeV):"));
  helium3MassLineEdit = new QLineEdit;
  connect(helium3MassLineEdit, &QLineEdit::textChanged, helium3Coalescence, &Coalescence::overWriteMass);
  helium3MassLineEdit->setText(tr("2.8085"));
  helium3MassLabel->setBuddy(helium3MassLineEdit);
  helium3pDiffCutLabel = new QLabel(tr("截断动量(GeV):"));
  helium3pDiffCutLineEdit = new QLineEdit;
  connect(helium3pDiffCutLineEdit, &QLineEdit::textChanged, helium3Coalescence, &Coalescence::overWritepDiffCut);
  helium3pDiffCutLineEdit->setText(tr("0.08"));
  helium3pDiffCutLabel->setBuddy(helium3pDiffCutLineEdit);

  helium3BaseInformationGridLayout = new QGridLayout;
  helium3BaseInformationGridLayout->addWidget(helium3MassLabel, 0, 0, 1, 1);
  helium3BaseInformationGridLayout->addWidget(helium3MassLineEdit, 0, 1, 1, 1);
  helium3BaseInformationGridLayout->addWidget(helium3pDiffCutLabel, 1, 0, 1, 1);
  helium3BaseInformationGridLayout->addWidget(helium3pDiffCutLineEdit, 1, 1, 1, 1);
  helium3InformationGroupBox->setLayout(helium3BaseInformationGridLayout);

  helium3CutGroupBox = new QGroupBox(tr("运动学窗口信息"));
  helium3PtLowLabel = new QLabel(tr("Pt下限:"));
  helium3PtLowDoubleSpinBox = new QDoubleSpinBox;
  connect(helium3PtLowDoubleSpinBox, SIGNAL(valueChanged(double)), helium3Coalescence, SLOT(overWritePtLow(double)));
  helium3PtLowDoubleSpinBox->setRange(0.0, 5.0);
  helium3PtLowDoubleSpinBox->setValue(0.4);
  helium3PtLowDoubleSpinBox->setSingleStep(0.1);

  helium3PtHighLabel = new QLabel(tr("Pt上限:"));
  helium3PtHighDoubleSpinBox = new QDoubleSpinBox;
  connect(helium3PtHighDoubleSpinBox, SIGNAL(valueChanged(double)), helium3Coalescence, SLOT(overWritePtHigh(double)));
  helium3PtHighDoubleSpinBox->setRange(0.0, 5.0);
  helium3PtHighDoubleSpinBox->setValue(2.0);
  helium3PtHighDoubleSpinBox->setSingleStep(0.1);

  helium3RapidityLowLabel = new QLabel(tr("快度下限:"));
  helium3RapidityLowDoubleSpinBox = new QDoubleSpinBox;
  connect(helium3RapidityLowDoubleSpinBox, SIGNAL(valueChanged(double)), helium3Coalescence, SLOT(overWriteRapidityLow(double)));
  helium3RapidityLowDoubleSpinBox->setRange(-4.0, 4.0);
  helium3RapidityLowDoubleSpinBox->setValue(-0.5);
  helium3RapidityLowDoubleSpinBox->setSingleStep(0.1);

  helium3RapidityHighLabel = new QLabel(tr("快度上限:"));
  helium3RapidityHighDoubleSpinBox = new QDoubleSpinBox;
  connect(helium3RapidityHighDoubleSpinBox, SIGNAL(valueChanged(double)), helium3Coalescence, SLOT(overWriteRapidityHigh(double)));
  helium3RapidityHighDoubleSpinBox->setRange(-4.0, 4.0);
  helium3RapidityHighDoubleSpinBox->setValue(0.5);
  helium3RapidityHighDoubleSpinBox->setSingleStep(0.1);

  helium3CentralityLowLabel = new QLabel(tr("中心度下限:"));
  helium3CentralityLowSpinBox = new QSpinBox;
  connect(helium3CentralityLowSpinBox, SIGNAL(valueChanged(int)), helium3Coalescence, SLOT(overWriteCentralityLow(int)));
  helium3CentralityLowSpinBox->setRange(0, 100);
  helium3CentralityLowSpinBox->setSingleStep(1);
  helium3CentralityLowSpinBox->setSuffix("%");
  helium3CentralityLowSpinBox->setValue(0);

  helium3CentralityHighLabel = new QLabel(tr("中心度上限:"));
  helium3CentralityHighSpinBox = new QSpinBox;
  connect(helium3CentralityHighSpinBox, SIGNAL(valueChanged(int)), helium3Coalescence, SLOT(overWriteCentralityHigh(int)));
  helium3CentralityHighSpinBox->setRange(0, 100);
  helium3CentralityHighSpinBox->setSingleStep(1);
  helium3CentralityHighSpinBox->setSuffix("%");
  helium3CentralityHighSpinBox->setValue(80);

  helium3CutGridLayout = new QGridLayout;
  helium3CutGridLayout->addWidget(helium3PtLowLabel, 0, 0, 1, 1);
  helium3CutGridLayout->addWidget(helium3PtLowDoubleSpinBox, 0, 1, 1, 1);
  helium3CutGridLayout->addWidget(helium3PtHighLabel, 0, 2, 1, 1);
  helium3CutGridLayout->addWidget(helium3PtHighDoubleSpinBox, 0, 3, 1, 1);
  helium3CutGridLayout->addWidget(helium3RapidityLowLabel, 1, 0, 1, 1);
  helium3CutGridLayout->addWidget(helium3RapidityLowDoubleSpinBox, 1, 1, 1, 1);
  helium3CutGridLayout->addWidget(helium3RapidityHighLabel, 1, 2, 1, 1);
  helium3CutGridLayout->addWidget(helium3RapidityHighDoubleSpinBox, 1, 3, 1, 1);
  helium3CutGridLayout->addWidget(helium3CentralityLowLabel, 2, 0, 1, 1);
  helium3CutGridLayout->addWidget(helium3CentralityLowSpinBox, 2, 1, 1, 1);
  helium3CutGridLayout->addWidget(helium3CentralityHighLabel, 2, 2, 1, 1);
  helium3CutGridLayout->addWidget(helium3CentralityHighSpinBox, 2, 3, 1, 1);

  helium3CutGroupBox->setLayout(helium3CutGridLayout);

  helium3MainLayout = new QVBoxLayout;
  helium3MainLayout->addWidget(helium3InformationGroupBox);
  helium3MainLayout->addWidget(helium3CutGroupBox);

  helium3Widget->setLayout(helium3MainLayout);
}

void MainWindow::createAntiHelium3Widget() {
  antiHelium3Widget = new QWidget(this);

  antiHelium3Coalescence = new Coalescence(antiHelium3Widget);

  antiHelium3InformationGroupBox = new QGroupBox(tr("是否想生成氦3"));
  antiHelium3InformationGroupBox->setCheckable(true);
  antiHelium3InformationGroupBox->setChecked(false);

  antiHelium3MassLabel = new QLabel(tr("核质量(GeV):"));
  antiHelium3MassLineEdit = new QLineEdit;
  connect(antiHelium3MassLineEdit, &QLineEdit::textChanged, antiHelium3Coalescence, &Coalescence::overWriteMass);
  antiHelium3MassLineEdit->setText(tr("2.8085"));
  antiHelium3MassLabel->setBuddy(antiHelium3MassLineEdit);
  antiHelium3pDiffCutLabel = new QLabel(tr("截断动量(GeV):"));
  antiHelium3pDiffCutLineEdit = new QLineEdit;
  connect(antiHelium3pDiffCutLineEdit, &QLineEdit::textChanged, antiHelium3Coalescence, &Coalescence::overWritepDiffCut);
  antiHelium3pDiffCutLineEdit->setText(tr("0.08"));
  antiHelium3pDiffCutLabel->setBuddy(antiHelium3pDiffCutLineEdit);

  antiHelium3BaseInformationGridLayout = new QGridLayout;
  antiHelium3BaseInformationGridLayout->addWidget(antiHelium3MassLabel, 0, 0, 1, 1);
  antiHelium3BaseInformationGridLayout->addWidget(antiHelium3MassLineEdit, 0, 1, 1, 1);
  antiHelium3BaseInformationGridLayout->addWidget(antiHelium3pDiffCutLabel, 1, 0, 1, 1);
  antiHelium3BaseInformationGridLayout->addWidget(antiHelium3pDiffCutLineEdit, 1, 1, 1, 1);
  antiHelium3InformationGroupBox->setLayout(antiHelium3BaseInformationGridLayout);

  antiHelium3CutGroupBox = new QGroupBox(tr("运动学窗口信息"));
  antiHelium3PtLowLabel = new QLabel(tr("Pt下限:"));
  antiHelium3PtLowDoubleSpinBox = new QDoubleSpinBox;
  connect(antiHelium3PtLowDoubleSpinBox, SIGNAL(valueChanged(double)), antiHelium3Coalescence, SLOT(overWritePtLow(double)));
  antiHelium3PtLowDoubleSpinBox->setRange(0.0, 5.0);
  antiHelium3PtLowDoubleSpinBox->setValue(0.4);
  antiHelium3PtLowDoubleSpinBox->setSingleStep(0.1);

  antiHelium3PtHighLabel = new QLabel(tr("Pt上限:"));
  antiHelium3PtHighDoubleSpinBox = new QDoubleSpinBox;
  connect(antiHelium3PtHighDoubleSpinBox, SIGNAL(valueChanged(double)), antiHelium3Coalescence, SLOT(overWritePtHigh(double)));
  antiHelium3PtHighDoubleSpinBox->setRange(0.0, 5.0);
  antiHelium3PtHighDoubleSpinBox->setValue(2.0);
  antiHelium3PtHighDoubleSpinBox->setSingleStep(0.1);

  antiHelium3RapidityLowLabel = new QLabel(tr("快度下限:"));
  antiHelium3RapidityLowDoubleSpinBox = new QDoubleSpinBox;
  connect(antiHelium3RapidityLowDoubleSpinBox, SIGNAL(valueChanged(double)), antiHelium3Coalescence, SLOT(overWriteRapidityLow(double)));
  antiHelium3RapidityLowDoubleSpinBox->setRange(-4.0, 4.0);
  antiHelium3RapidityLowDoubleSpinBox->setValue(-0.5);
  antiHelium3RapidityLowDoubleSpinBox->setSingleStep(0.1);

  antiHelium3RapidityHighLabel = new QLabel(tr("快度上限:"));
  antiHelium3RapidityHighDoubleSpinBox = new QDoubleSpinBox;
  connect(antiHelium3RapidityHighDoubleSpinBox, SIGNAL(valueChanged(double)), antiHelium3Coalescence, SLOT(overWriteRapidityHigh(double)));
  antiHelium3RapidityHighDoubleSpinBox->setRange(-4.0, 4.0);
  antiHelium3RapidityHighDoubleSpinBox->setValue(0.5);
  antiHelium3RapidityHighDoubleSpinBox->setSingleStep(0.1);

  antiHelium3CentralityLowLabel = new QLabel(tr("中心度下限:"));
  antiHelium3CentralityLowSpinBox = new QSpinBox;
  connect(antiHelium3CentralityLowSpinBox, SIGNAL(valueChanged(int)), antiHelium3Coalescence, SLOT(overWriteCentralityLow(int)));
  antiHelium3CentralityLowSpinBox->setRange(0, 100);
  antiHelium3CentralityLowSpinBox->setSingleStep(1);
  antiHelium3CentralityLowSpinBox->setSuffix("%");
  antiHelium3CentralityLowSpinBox->setValue(0);

  antiHelium3CentralityHighLabel = new QLabel(tr("中心度上限:"));
  antiHelium3CentralityHighSpinBox = new QSpinBox;
  connect(antiHelium3CentralityHighSpinBox, SIGNAL(valueChanged(int)), antiHelium3Coalescence, SLOT(overWriteCentralityHigh(int)));
  antiHelium3CentralityHighSpinBox->setRange(0, 100);
  antiHelium3CentralityHighSpinBox->setSingleStep(1);
  antiHelium3CentralityHighSpinBox->setSuffix("%");
  antiHelium3CentralityHighSpinBox->setValue(80);

  antiHelium3CutGridLayout = new QGridLayout;
  antiHelium3CutGridLayout->addWidget(antiHelium3PtLowLabel, 0, 0, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3PtLowDoubleSpinBox, 0, 1, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3PtHighLabel, 0, 2, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3PtHighDoubleSpinBox, 0, 3, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3RapidityLowLabel, 1, 0, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3RapidityLowDoubleSpinBox, 1, 1, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3RapidityHighLabel, 1, 2, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3RapidityHighDoubleSpinBox, 1, 3, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3CentralityLowLabel, 2, 0, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3CentralityLowSpinBox, 2, 1, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3CentralityHighLabel, 2, 2, 1, 1);
  antiHelium3CutGridLayout->addWidget(antiHelium3CentralityHighSpinBox, 2, 3, 1, 1);

  antiHelium3CutGroupBox->setLayout(antiHelium3CutGridLayout);

  antiHelium3MainLayout = new QVBoxLayout;
  antiHelium3MainLayout->addWidget(antiHelium3InformationGroupBox);
  antiHelium3MainLayout->addWidget(antiHelium3CutGroupBox);

  antiHelium3Widget->setLayout(antiHelium3MainLayout);
}

void MainWindow::createHypertritonWidget() {
  hypertritonWidget = new QWidget(this);

  hypertritonCoalescence = new Coalescence(hypertritonWidget);

  hypertritonInformationGroupBox = new QGroupBox(tr("是否想生成氦3"));
  hypertritonInformationGroupBox->setCheckable(true);
  hypertritonInformationGroupBox->setChecked(false);

  hypertritonMassLabel = new QLabel(tr("核质量(GeV):"));
  hypertritonMassLineEdit = new QLineEdit;
  connect(hypertritonMassLineEdit, &QLineEdit::textChanged, hypertritonCoalescence, &Coalescence::overWriteMass);
  hypertritonMassLineEdit->setText(tr("2.8085"));
  hypertritonMassLabel->setBuddy(hypertritonMassLineEdit);
  hypertritonpDiffCutLabel = new QLabel(tr("截断动量(GeV):"));
  hypertritonpDiffCutLineEdit = new QLineEdit;
  connect(hypertritonpDiffCutLineEdit, &QLineEdit::textChanged, hypertritonCoalescence, &Coalescence::overWritepDiffCut);
  hypertritonpDiffCutLineEdit->setText(tr("0.08"));
  hypertritonpDiffCutLabel->setBuddy(hypertritonpDiffCutLineEdit);

  hypertritonBaseInformationGridLayout = new QGridLayout;
  hypertritonBaseInformationGridLayout->addWidget(hypertritonMassLabel, 0, 0, 1, 1);
  hypertritonBaseInformationGridLayout->addWidget(hypertritonMassLineEdit, 0, 1, 1, 1);
  hypertritonBaseInformationGridLayout->addWidget(hypertritonpDiffCutLabel, 1, 0, 1, 1);
  hypertritonBaseInformationGridLayout->addWidget(hypertritonpDiffCutLineEdit, 1, 1, 1, 1);
  hypertritonInformationGroupBox->setLayout(hypertritonBaseInformationGridLayout);

  hypertritonCutGroupBox = new QGroupBox(tr("运动学窗口信息"));
  hypertritonPtLowLabel = new QLabel(tr("Pt下限:"));
  hypertritonPtLowDoubleSpinBox = new QDoubleSpinBox;
  connect(hypertritonPtLowDoubleSpinBox, SIGNAL(valueChanged(double)), hypertritonCoalescence, SLOT(overWritePtLow(double)));
  hypertritonPtLowDoubleSpinBox->setRange(0.0, 5.0);
  hypertritonPtLowDoubleSpinBox->setValue(0.4);
  hypertritonPtLowDoubleSpinBox->setSingleStep(0.1);

  hypertritonPtHighLabel = new QLabel(tr("Pt上限:"));
  hypertritonPtHighDoubleSpinBox = new QDoubleSpinBox;
  connect(hypertritonPtHighDoubleSpinBox, SIGNAL(valueChanged(double)), hypertritonCoalescence, SLOT(overWritePtHigh(double)));
  hypertritonPtHighDoubleSpinBox->setRange(0.0, 5.0);
  hypertritonPtHighDoubleSpinBox->setValue(2.0);
  hypertritonPtHighDoubleSpinBox->setSingleStep(0.1);

  hypertritonRapidityLowLabel = new QLabel(tr("快度下限:"));
  hypertritonRapidityLowDoubleSpinBox = new QDoubleSpinBox;
  connect(hypertritonRapidityLowDoubleSpinBox, SIGNAL(valueChanged(double)), hypertritonCoalescence, SLOT(overWriteRapidityLow(double)));
  hypertritonRapidityLowDoubleSpinBox->setRange(-4.0, 4.0);
  hypertritonRapidityLowDoubleSpinBox->setValue(-0.5);
  hypertritonRapidityLowDoubleSpinBox->setSingleStep(0.1);

  hypertritonRapidityHighLabel = new QLabel(tr("快度上限:"));
  hypertritonRapidityHighDoubleSpinBox = new QDoubleSpinBox;
  connect(hypertritonRapidityHighDoubleSpinBox, SIGNAL(valueChanged(double)), hypertritonCoalescence, SLOT(overWriteRapidityHigh(double)));
  hypertritonRapidityHighDoubleSpinBox->setRange(-4.0, 4.0);
  hypertritonRapidityHighDoubleSpinBox->setValue(0.5);
  hypertritonRapidityHighDoubleSpinBox->setSingleStep(0.1);

  hypertritonCentralityLowLabel = new QLabel(tr("中心度下限:"));
  hypertritonCentralityLowSpinBox = new QSpinBox;
  connect(hypertritonCentralityLowSpinBox, SIGNAL(valueChanged(int)), hypertritonCoalescence, SLOT(overWriteCentralityLow(int)));
  hypertritonCentralityLowSpinBox->setRange(0, 100);
  hypertritonCentralityLowSpinBox->setSingleStep(1);
  hypertritonCentralityLowSpinBox->setSuffix("%");
  hypertritonCentralityLowSpinBox->setValue(0);

  hypertritonCentralityHighLabel = new QLabel(tr("中心度上限:"));
  hypertritonCentralityHighSpinBox = new QSpinBox;
  connect(hypertritonCentralityHighSpinBox, SIGNAL(valueChanged(int)), hypertritonCoalescence, SLOT(overWriteCentralityHigh(int)));
  hypertritonCentralityHighSpinBox->setRange(0, 100);
  hypertritonCentralityHighSpinBox->setSingleStep(1);
  hypertritonCentralityHighSpinBox->setSuffix("%");
  hypertritonCentralityHighSpinBox->setValue(80);

  hypertritonCutGridLayout = new QGridLayout;
  hypertritonCutGridLayout->addWidget(hypertritonPtLowLabel, 0, 0, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonPtLowDoubleSpinBox, 0, 1, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonPtHighLabel, 0, 2, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonPtHighDoubleSpinBox, 0, 3, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonRapidityLowLabel, 1, 0, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonRapidityLowDoubleSpinBox, 1, 1, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonRapidityHighLabel, 1, 2, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonRapidityHighDoubleSpinBox, 1, 3, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonCentralityLowLabel, 2, 0, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonCentralityLowSpinBox, 2, 1, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonCentralityHighLabel, 2, 2, 1, 1);
  hypertritonCutGridLayout->addWidget(hypertritonCentralityHighSpinBox, 2, 3, 1, 1);

  hypertritonCutGroupBox->setLayout(hypertritonCutGridLayout);

  hypertritonMainLayout = new QVBoxLayout;
  hypertritonMainLayout->addWidget(hypertritonInformationGroupBox);
  hypertritonMainLayout->addWidget(hypertritonCutGroupBox);

  hypertritonWidget->setLayout(hypertritonMainLayout);
}

void MainWindow::createAntiHypertritonWidget() {
  antiHypertritonWidget = new QWidget(this);

  antiHypertritonCoalescence = new Coalescence(antiHypertritonWidget);

  antiHypertritonInformationGroupBox = new QGroupBox(tr("是否想生成氦3"));
  antiHypertritonInformationGroupBox->setCheckable(true);
  antiHypertritonInformationGroupBox->setChecked(false);

  antiHypertritonMassLabel = new QLabel(tr("核质量(GeV):"));
  antiHypertritonMassLineEdit = new QLineEdit;
  connect(antiHypertritonMassLineEdit, &QLineEdit::textChanged, antiHypertritonCoalescence, &Coalescence::overWriteMass);
  antiHypertritonMassLineEdit->setText(tr("2.8085"));
  antiHypertritonMassLabel->setBuddy(antiHypertritonMassLineEdit);
  antiHypertritonpDiffCutLabel = new QLabel(tr("截断动量(GeV):"));
  antiHypertritonpDiffCutLineEdit = new QLineEdit;
  connect(antiHypertritonpDiffCutLineEdit, &QLineEdit::textChanged, antiHypertritonCoalescence, &Coalescence::overWritepDiffCut);
  antiHypertritonpDiffCutLineEdit->setText(tr("0.08"));
  antiHypertritonpDiffCutLabel->setBuddy(antiHypertritonpDiffCutLineEdit);

  antiHypertritonBaseInformationGridLayout = new QGridLayout;
  antiHypertritonBaseInformationGridLayout->addWidget(antiHypertritonMassLabel, 0, 0, 1, 1);
  antiHypertritonBaseInformationGridLayout->addWidget(antiHypertritonMassLineEdit, 0, 1, 1, 1);
  antiHypertritonBaseInformationGridLayout->addWidget(antiHypertritonpDiffCutLabel, 1, 0, 1, 1);
  antiHypertritonBaseInformationGridLayout->addWidget(antiHypertritonpDiffCutLineEdit, 1, 1, 1, 1);
  antiHypertritonInformationGroupBox->setLayout(antiHypertritonBaseInformationGridLayout);

  antiHypertritonCutGroupBox = new QGroupBox(tr("运动学窗口信息"));
  antiHypertritonPtLowLabel = new QLabel(tr("Pt下限:"));
  antiHypertritonPtLowDoubleSpinBox = new QDoubleSpinBox;
  connect(antiHypertritonPtLowDoubleSpinBox, SIGNAL(valueChanged(double)), antiHypertritonCoalescence, SLOT(overWritePtLow(double)));
  antiHypertritonPtLowDoubleSpinBox->setRange(0.0, 5.0);
  antiHypertritonPtLowDoubleSpinBox->setValue(0.4);
  antiHypertritonPtLowDoubleSpinBox->setSingleStep(0.1);

  antiHypertritonPtHighLabel = new QLabel(tr("Pt上限:"));
  antiHypertritonPtHighDoubleSpinBox = new QDoubleSpinBox;
  connect(antiHypertritonPtHighDoubleSpinBox, SIGNAL(valueChanged(double)), antiHypertritonCoalescence, SLOT(overWritePtHigh(double)));
  antiHypertritonPtHighDoubleSpinBox->setRange(0.0, 5.0);
  antiHypertritonPtHighDoubleSpinBox->setValue(2.0);
  antiHypertritonPtHighDoubleSpinBox->setSingleStep(0.1);

  antiHypertritonRapidityLowLabel = new QLabel(tr("快度下限:"));
  antiHypertritonRapidityLowDoubleSpinBox = new QDoubleSpinBox;
  connect(antiHypertritonRapidityLowDoubleSpinBox, SIGNAL(valueChanged(double)), antiHypertritonCoalescence, SLOT(overWriteRapidityLow(double)));
  antiHypertritonRapidityLowDoubleSpinBox->setRange(-4.0, 4.0);
  antiHypertritonRapidityLowDoubleSpinBox->setValue(-0.5);
  antiHypertritonRapidityLowDoubleSpinBox->setSingleStep(0.1);

  antiHypertritonRapidityHighLabel = new QLabel(tr("快度上限:"));
  antiHypertritonRapidityHighDoubleSpinBox = new QDoubleSpinBox;
  connect(antiHypertritonRapidityHighDoubleSpinBox, SIGNAL(valueChanged(double)), antiHypertritonCoalescence, SLOT(overWriteRapidityHigh(double)));
  antiHypertritonRapidityHighDoubleSpinBox->setRange(-4.0, 4.0);
  antiHypertritonRapidityHighDoubleSpinBox->setValue(0.5);
  antiHypertritonRapidityHighDoubleSpinBox->setSingleStep(0.1);

  antiHypertritonCentralityLowLabel = new QLabel(tr("中心度下限:"));
  antiHypertritonCentralityLowSpinBox = new QSpinBox;
  connect(antiHypertritonCentralityLowSpinBox, SIGNAL(valueChanged(int)), antiHypertritonCoalescence, SLOT(overWriteCentralityLow(int)));
  antiHypertritonCentralityLowSpinBox->setRange(0, 100);
  antiHypertritonCentralityLowSpinBox->setSingleStep(1);
  antiHypertritonCentralityLowSpinBox->setSuffix("%");
  antiHypertritonCentralityLowSpinBox->setValue(0);

  antiHypertritonCentralityHighLabel = new QLabel(tr("中心度上限:"));
  antiHypertritonCentralityHighSpinBox = new QSpinBox;
  connect(antiHypertritonCentralityHighSpinBox, SIGNAL(valueChanged(int)), antiHypertritonCoalescence, SLOT(overWriteCentralityHigh(int)));
  antiHypertritonCentralityHighSpinBox->setRange(0, 100);
  antiHypertritonCentralityHighSpinBox->setSingleStep(1);
  antiHypertritonCentralityHighSpinBox->setSuffix("%");
  antiHypertritonCentralityHighSpinBox->setValue(80);

  antiHypertritonCutGridLayout = new QGridLayout;
  antiHypertritonCutGridLayout->addWidget(antiHypertritonPtLowLabel, 0, 0, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonPtLowDoubleSpinBox, 0, 1, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonPtHighLabel, 0, 2, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonPtHighDoubleSpinBox, 0, 3, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonRapidityLowLabel, 1, 0, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonRapidityLowDoubleSpinBox, 1, 1, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonRapidityHighLabel, 1, 2, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonRapidityHighDoubleSpinBox, 1, 3, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonCentralityLowLabel, 2, 0, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonCentralityLowSpinBox, 2, 1, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonCentralityHighLabel, 2, 2, 1, 1);
  antiHypertritonCutGridLayout->addWidget(antiHypertritonCentralityHighSpinBox, 2, 3, 1, 1);

  antiHypertritonCutGroupBox->setLayout(antiHypertritonCutGridLayout);

  antiHypertritonMainLayout = new QVBoxLayout;
  antiHypertritonMainLayout->addWidget(antiHypertritonInformationGroupBox);
  antiHypertritonMainLayout->addWidget(antiHypertritonCutGroupBox);

  antiHypertritonWidget->setLayout(antiHypertritonMainLayout);
}

void MainWindow::createLayout() {
  QGridLayout *topLayout = new QGridLayout;
  topLayout->addWidget(inputFileListLabel, 0, 0, 1, 1);
  topLayout->addWidget(inputFileListLineEdit, 0, 1, 1, 1);
  topLayout->addWidget(resultFileLabel, 1, 0, 1, 1);
  topLayout->addWidget(resultFileLineEdit, 1, 1, 1, 1);

  QStackedLayout *stackedLayout = new QStackedLayout;
  stackedLayout->addWidget(helium3Widget);
  stackedLayout->addWidget(antiHelium3Widget);
  stackedLayout->addWidget(hypertritonWidget);
  stackedLayout->addWidget(antiHypertritonWidget);

  connect(listWidget, &QListWidget::currentRowChanged, stackedLayout, &QStackedLayout::setCurrentIndex);
  listWidget->setCurrentRow(0);

  QGridLayout *middleLayout = new QGridLayout;
  middleLayout->addWidget(listWidget, 0, 0, 1, 1);
  middleLayout->addLayout(stackedLayout, 0, 1, 1, 1);
  middleLayout->setColumnStretch(0, 1);
  middleLayout->setColumnStretch(1, 3);

  QHBoxLayout *bottomLayout = new QHBoxLayout;
  bottomLayout->addStretch();
  bottomLayout->addWidget(cancelPushButton);
  bottomLayout->addWidget(okPushButton);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(topLayout);
  mainLayout->addLayout(middleLayout);
  mainLayout->addLayout(bottomLayout);

  centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);
  this->setCentralWidget(centralWidget);
}

void MainWindow::createOthersWidget() {
  inputFileListLabel = new QLabel(tr("输入文件列表:"));
  inputFileListLineEdit = new QLineEdit;
  inputFileListLabel->setBuddy(inputFileListLineEdit);
  inputFileListLineEdit->setText(QDir::currentPath() + QStringLiteral("/data/data.list"));

  resultFileLabel = new QLabel(tr("结果文件:"));
  resultFileLineEdit = new QLineEdit;
  resultFileLabel->setBuddy(resultFileLineEdit);
  resultFileLineEdit->setText(tr("/home/xiaohai/result.root"));

  cancelPushButton = new QPushButton(tr("取消"));
  okPushButton = new QPushButton(tr("确定"));

  // link signal and slot
  connect(okPushButton, &QPushButton::clicked, this, &MainWindow::runCoalescence);
  connect(cancelPushButton, &QPushButton::clicked, this, &MainWindow::close);
}
