#include <iostream>

#include <QDir>
#include <QFile>
#include <QTextStream>

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"

#include "AMPT.h"
#include "jglobal.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  settingDefaultParameters();

  //! connect SIGNALS and SLOTS
  connect(ui->helium3CheckBox, SIGNAL(stateChanged(int)), this,
          SLOT(isGenerateHelium3(int)));
  connect(ui->antiHelium3CheckBox, SIGNAL(stateChanged(int)), this,
          SLOT(isGenerateAntiHelium3(int)));
  connect(ui->hypertritonCheckBox, SIGNAL(stateChanged(int)), this,
          SLOT(isGenerateHypertriton(int)));
  connect(ui->antiHypertritonCheckBox, SIGNAL(stateChanged(int)), this,
          SLOT(isGenerateAntiHypertriton(int)));

  //!
  connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::run);
  connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::settingDefaultParameters() {
  this->ui->inputFileListLineEdit->setText(QDir::currentPath() +
                                           "/list/data.list");
}

void MainWindow::initHistogram() {
  TH1D *helium3dNdy = new TH1D("helium3dNdy", "helium3dNdy", 30, -3, 3);
  TH1D *helium3dNdydPt = new TH1D("helium3dNdydPt", "helium3dNdydPt", 30, 0, 3);
}

void MainWindow::loadData() {
  QString inputFileList = this->ui->inputFileListLineEdit->text();
  QFile file(inputFileList);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    std::cout << "Can not open file for reading: "
              << qPrintable(file.errorString()) << std::endl;
  }

  chain = new TChain("AMPT");
  QTextStream in(&file);
  while (!in.atEnd()) {
    QString eachRootFile = in.readLine();
    TFile *testRootFile = new TFile(eachRootFile.toStdString().c_str());
    if (!testRootFile || !testRootFile->IsOpen() || !testRootFile->GetNkeys()) {
      std::cout << "The root file is bad :" << qPrintable(eachRootFile)
                << std::endl;
    } else {
      chain->Add(eachRootFile.toStdString().c_str());
    }
    delete testRootFile;
  }
}

void MainWindow::writeData() {
  helium3dNdy->Write();
  helium3dNdydPt->Write();
}

void MainWindow::changeEvent(QEvent *e) {
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

void MainWindow::isGenerateHelium3(int checkBoxState) {
  bool state = (checkBoxState == Qt::CheckState::Checked) ? true : false;
  ui->helium3PIDLineEdit->setEnabled(state);
  ui->helium3MassLineEdit->setEnabled(state);
  ui->helium3WaitingLineEdit->setEnabled(state);
  ui->helium3CentralityLowLineEdit->setEnabled(state);
  ui->helium3CentralityHighLineEdit->setEnabled(state);
  ui->helium3PtLowLineEdit->setEnabled(state);
  ui->helium3PtHighLineEdit->setEnabled(state);
  ui->helium3RapidityLowLineEdit->setEnabled(state);
  ui->helium3RapidityHighLineEdit->setEnabled(state);
}

void MainWindow::isGenerateAntiHelium3(int checkBoxState) {
  bool state = (checkBoxState == Qt::CheckState::Checked) ? true : false;
  ui->antiHelium3PIDLineEdit->setEnabled(state);
  ui->antiHelium3MassLineEdit->setEnabled(state);
  ui->antiHelium3WaitingLineEdit->setEnabled(state);
  ui->antiHelium3CentralityLowLineEdit->setEnabled(state);
  ui->antiHelium3CentralityHighLineEdit->setEnabled(state);
  ui->antiHelium3PtLowLineEdit->setEnabled(state);
  ui->antiHelium3PtHighLineEdit->setEnabled(state);
  ui->antiHelium3RapidityLowLineEdit->setEnabled(state);
  ui->antiHelium3RapidityHighLineEdit->setEnabled(state);
}

void MainWindow::isGenerateHypertriton(int checkBoxState) {
  bool state = (checkBoxState == Qt::CheckState::Checked) ? true : false;
  ui->hypertritonPIDLineEdit->setEnabled(state);
  ui->hypertritonMassLineEdit->setEnabled(state);
  ui->hypertritonWaitingLineEdit->setEnabled(state);
  ui->hypertritonCentralityLowLineEdit->setEnabled(state);
  ui->hypertritonCentralityHighLineEdit->setEnabled(state);
  ui->hypertritonPtLowLineEdit->setEnabled(state);
  ui->hypertritonPtHighLineEdit->setEnabled(state);
  ui->hypertritonRapidityLowLineEdit->setEnabled(state);
  ui->hypertritonRapidityHighLineEdit->setEnabled(state);
}

void MainWindow::isGenerateAntiHypertriton(int checkBoxState) {
  bool state = (checkBoxState == Qt::CheckState::Checked) ? true : false;
  ui->antiHypertritonPIDLineEdit->setEnabled(state);
  ui->antiHypertritonMassLineEdit->setEnabled(state);
  ui->antiHypertritonWaitingLineEdit->setEnabled(state);
  ui->antiHypertritonCentralityLowLineEdit->setEnabled(state);
  ui->antiHypertritonCentralityHighLineEdit->setEnabled(state);
  ui->antiHypertritonPtLowLineEdit->setEnabled(state);
  ui->antiHypertritonPtHighLineEdit->setEnabled(state);
  ui->antiHypertritonRapidityLowLineEdit->setEnabled(state);
  ui->antiHypertritonRapidityHighLineEdit->setEnabled(state);
}

void MainWindow::run() {
  initHistogram();
  this->loadData();
}
