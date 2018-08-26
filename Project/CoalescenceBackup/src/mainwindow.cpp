#include <cmath>
#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"

#include "AMPT.h"
#include "mainwindow.h"
#include "track.h"
#include "ui_mainwindow.h"

/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setDefaultParameters();
  setHistograms();

  //! connect SIGNALS and SLOTS
  connect(ui->helium3CheckBox, SIGNAL(stateChanged(int)), this, SLOT(isGenerateHelium3(int)));
  connect(ui->antiHelium3CheckBox, SIGNAL(stateChanged(int)), this, SLOT(isGenerateAntiHelium3(int)));
  connect(ui->hypertritonCheckBox, SIGNAL(stateChanged(int)), this, SLOT(isGenerateHypertriton(int)));
  connect(ui->antiHypertritonCheckBox, SIGNAL(stateChanged(int)), this, SLOT(isGenerateAntiHypertriton(int)));

  //!
  connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::run);
  connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);

  //!
  connect(ui->quitAction, &QAction::triggered, this, &MainWindow::close);
}

/*!
 * \brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
  delete ui;

  delete helium3dNdy;
  delete helium3dNdydPt;
  delete antiHelium3dNdy;
  delete antiHelium3dNdydPt;
  delete hypertritondNdy;
  delete hypertritondNdydPt;
  delete antiHypertritondNdy;
  delete antiHypertritondNdydPt;

  delete chain;
}

/*!
 * \brief MainWindow::settingDefaultParameters
 */
void MainWindow::setDefaultParameters() {
  this->ui->inputFileListLineEdit->setText(QDir::currentPath() + "/list/data.list");
  this->ui->resultFileNameLineEdit->setText(QDir::currentPath() + "/result/result.root");
}

void MainWindow::setHistograms() {
  helium3dNdy =
      new TH1D("helium3dNdy", "helium3dNdy", ui->helium3dNdyLineEdit->text().toInt(),
               ui->helium3RapidityLowLineEdit->text().toDouble(), ui->helium3RapidityHighLineEdit->text().toDouble());
  helium3dNdydPt = new TH1D("helium3dNdydPt", "helium3dNdydPt", ui->helium3dNdydPtLineEdit->text().toInt(),
                            ui->helium3PtLowLineEdit->text().toDouble(), ui->helium3PtHighLineEdit->text().toDouble());
  antiHelium3dNdy = new TH1D("antiHelium3dNdy", "antiHelium3dNdy", ui->antiHelium3dNdyLineEdit->text().toInt(),
                             ui->antiHelium3RapidityLowLineEdit->text().toDouble(),
                             ui->antiHelium3RapidityHighLineEdit->text().toDouble());
  antiHelium3dNdydPt =
      new TH1D("antiHelium3dNdydPt", "antiHelium3dNdydPt", ui->antiHelium3dNdydPtLineEdit->text().toInt(),
               ui->antiHelium3PtLowLineEdit->text().toDouble(), ui->antiHelium3PtHighLineEdit->text().toDouble());

  hypertritondNdy = new TH1D("hypertritondNdy", "hypertritondNdy", ui->hypertritondNdyLineEdit->text().toInt(),
                             ui->hypertritonRapidityLowLineEdit->text().toDouble(),
                             ui->hypertritonRapidityHighLineEdit->text().toDouble());
  hypertritondNdydPt =
      new TH1D("hypertritondNdydPt", "hypertritondNdydPt", ui->hypertritondNdydPtLineEdit->text().toInt(),
               ui->hypertritonPtLowLineEdit->text().toDouble(), ui->hypertritonPtHighLineEdit->text().toDouble());
  antiHypertritondNdy =
      new TH1D("antiHypertritondNdy", "antiHypertritondNdy", ui->antiHypertritondNdyLineEdit->text().toInt(),
               ui->antiHypertritonRapidityLowLineEdit->text().toDouble(),
               ui->antiHypertritonRapidityHighLineEdit->text().toDouble());
  antiHypertritondNdydPt = new TH1D(
      "antiHypertritondNdydPt", "antiHypertritondNdydPt", ui->antiHypertritondNdydPtLineEdit->text().toInt(),
      ui->antiHypertritonPtLowLineEdit->text().toDouble(), ui->antiHypertritonPtHighLineEdit->text().toDouble());

  resultFile = new TFile(ui->resultFileNameLineEdit->text().split("/").last().toStdString().c_str(), "RECREATE");
}

/*!
 * \brief MainWindow::loadData
 */
void MainWindow::loadData() {
  QString inputFileList = this->ui->inputFileListLineEdit->text();
  QFile file(inputFileList);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    std::cout << "Can not open file for reading: " << qPrintable(file.errorString()) << std::endl;
  }

  chain = new TChain("AMPT");
  QTextStream in(&file);
  while (!in.atEnd()) {
    QString eachRootFile = in.readLine();
    TFile* testRootFile = new TFile(eachRootFile.toStdString().c_str());
    if (!testRootFile || !testRootFile->IsOpen() || !testRootFile->GetNkeys()) {
      std::cout << "The root file is bad :" << qPrintable(eachRootFile) << std::endl;
    } else {
      chain->Add(eachRootFile.toStdString().c_str());
    }
    delete testRootFile;
  }
}

void MainWindow::readInBuffer(AMPT*& ampt) {
  protonTracks.clear();
  antiProtonTracks.clear();
  neutronTracks.clear();
  antiNeutronTracks.clear();
  lambdaTracks.clear();
  antiLambdaTracks.clear();

  int multiTracks = ampt->Event_multi;
  int PID = 0;
  double Px = 0., Py = 0., Pz = 0., Energy = 0.;
  double X = 0., Y = 0., Z = 0., Time = 0.;

  for (int i = 0; i != multiTracks; ++i) {
    PID = ampt->ID[i];
    Track::dealMomentum(ampt->Px[i], ampt->Py[i], ampt->Pz[i], ampt->Mass[i], ampt->X[i], ampt->Y[i], ampt->Z[i],
                        ampt->Time[i], Px, Py, Pz, Energy, X, Y, Z, Time);
    if (PID == 2212) {
      protonTracks.push_back(Track(PID, Px, Py, Pz, Energy, X, Y, Z, Time, 1));
    } else if (PID == -2212) {
      antiProtonTracks.push_back(Track(PID, Px, Py, Pz, Energy, X, Y, Z, Time, 1));
    } else if (PID == 2112) {
      neutronTracks.push_back(Track(PID, Px, Py, Pz, Energy, X, Y, Z, Time, 1));
    } else if (PID == -2112) {
      antiNeutronTracks.push_back(Track(PID, Px, Py, Pz, Energy, X, Y, Z, Time, 1));
    } else if (PID == 3112) {
      lambdaTracks.push_back(Track(PID, Px, Py, Pz, Energy, X, Y, Z, Time, 1));
    } else if (PID == -3112) {
      antiLambdaTracks.push_back(Track(PID, Px, Py, Pz, Energy, X, Y, Z, Time, 1));
    }
  }
}

void MainWindow::loopEvent() {
  AMPT* ampt = new AMPT(this->chain);

  long int entries = chain->GetEntries();
  for (long int eachEvent = 0; eachEvent != entries; ++eachEvent) {
    this->chain->GetEntry(eachEvent);
    this->readInBuffer(ampt);

    if (ui->helium3CheckBox->isChecked()) {
      coalescence(Helium3);
    }
    if (ui->antiHelium3CheckBox->isChecked()) {
      coalescence(AntiHelium3);
    }
    if (ui->hypertritonCheckBox->isChecked()) {
      coalescence(Hypertriton);
    }
    if (ui->antiHypertritonCheckBox->isChecked()) {
      coalescence(AntiHypertriton);
    }
  }

  delete ampt;
}

/*!
 * \brief MainWindow::writeData
 */
void MainWindow::writeData() {
  resultFile->cd();
  helium3dNdy->Write();
  helium3dNdydPt->Write();
  antiHelium3dNdy->Write();
  antiHelium3dNdydPt->Write();
  hypertritondNdy->Write();
  hypertritondNdydPt->Write();
  antiHypertritondNdy->Write();
  antiHypertritondNdydPt->Write();

  resultFile->Close();
}

/*!
 * \brief MainWindow::coalescence
 * \param type
 */
void MainWindow::coalescence(PARTICLETYPE type) {
  switch (type) {
    case Helium3:
      coalescenceHelium3();
      break;
    case AntiHelium3:
      coalescenceAntiHelium3();
      break;
    case Hypertriton:
      coalescenceHypertriton();
      break;
    case AntiHypertriton:
      coalescenceAntiHypertriton();
      break;
    default:
      break;
  }
}

/*!
 * \brief MainWindow::changeEvent
 * \param e
 */
void MainWindow::changeEvent(QEvent* e) {
  QMainWindow::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
  }
}

/*!
 * \brief MainWindow::isGenerateHelium3
 * \param checkBoxState
 */
void MainWindow::isGenerateHelium3(int checkBoxState) {
  bool state = (checkBoxState == Qt::CheckState::Checked) ? true : false;
  ui->helium3dNdyLineEdit->setEnabled(state);
  ui->helium3MassLineEdit->setEnabled(state);
  ui->helium3dNdydPtLineEdit->setEnabled(state);
  ui->helium3CentralityLowLineEdit->setEnabled(state);
  ui->helium3CentralityHighLineEdit->setEnabled(state);
  ui->helium3PtLowLineEdit->setEnabled(state);
  ui->helium3PtHighLineEdit->setEnabled(state);
  ui->helium3RapidityLowLineEdit->setEnabled(state);
  ui->helium3RapidityHighLineEdit->setEnabled(state);
}

/*!
 * \brief MainWindow::isGenerateAntiHelium3
 * \param checkBoxState
 */
void MainWindow::isGenerateAntiHelium3(int checkBoxState) {
  bool state = (checkBoxState == Qt::CheckState::Checked) ? true : false;
  ui->antiHelium3dNdyLineEdit->setEnabled(state);
  ui->antiHelium3MassLineEdit->setEnabled(state);
  ui->antiHelium3dNdydPtLineEdit->setEnabled(state);
  ui->antiHelium3CentralityLowLineEdit->setEnabled(state);
  ui->antiHelium3CentralityHighLineEdit->setEnabled(state);
  ui->antiHelium3PtLowLineEdit->setEnabled(state);
  ui->antiHelium3PtHighLineEdit->setEnabled(state);
  ui->antiHelium3RapidityLowLineEdit->setEnabled(state);
  ui->antiHelium3RapidityHighLineEdit->setEnabled(state);
}

/*!
 * \brief MainWindow::isGenerateHypertriton
 * \param checkBoxState
 */
void MainWindow::isGenerateHypertriton(int checkBoxState) {
  bool state = (checkBoxState == Qt::CheckState::Checked) ? true : false;
  ui->hypertritondNdyLineEdit->setEnabled(state);
  ui->hypertritonMassLineEdit->setEnabled(state);
  ui->hypertritondNdydPtLineEdit->setEnabled(state);
  ui->hypertritonCentralityLowLineEdit->setEnabled(state);
  ui->hypertritonCentralityHighLineEdit->setEnabled(state);
  ui->hypertritonPtLowLineEdit->setEnabled(state);
  ui->hypertritonPtHighLineEdit->setEnabled(state);
  ui->hypertritonRapidityLowLineEdit->setEnabled(state);
  ui->hypertritonRapidityHighLineEdit->setEnabled(state);
}

/*!
 * \brief MainWindow::isGenerateAntiHypertriton
 * \param checkBoxState
 */
void MainWindow::isGenerateAntiHypertriton(int checkBoxState) {
  bool state = (checkBoxState == Qt::CheckState::Checked) ? true : false;
  ui->antiHypertritondNdyLineEdit->setEnabled(state);
  ui->antiHypertritonMassLineEdit->setEnabled(state);
  ui->antiHypertritondNdydPtLineEdit->setEnabled(state);
  ui->antiHypertritonCentralityLowLineEdit->setEnabled(state);
  ui->antiHypertritonCentralityHighLineEdit->setEnabled(state);
  ui->antiHypertritonPtLowLineEdit->setEnabled(state);
  ui->antiHypertritonPtHighLineEdit->setEnabled(state);
  ui->antiHypertritonRapidityLowLineEdit->setEnabled(state);
  ui->antiHypertritonRapidityHighLineEdit->setEnabled(state);
}

/*!
 * \brief MainWindow::run
 */
void MainWindow::run() {
  this->loadData();
  this->loopEvent();
  this->writeData();
}

void MainWindow::coalescenceHelium3() {
  for (int ip = 0; ip != protonTracks.size(); ++ip) {
    if (protonTracks[ip].getFlag() == 0) continue;
    for (int jp = ip + 1; jp != protonTracks.size(); ++jp) {
      if (protonTracks[ip].getFlag() * protonTracks[jp].getFlag() == 0) continue;
      for (int in = 0; in != neutronTracks.size(); ++in) {
        if (neutronTracks[in].getFlag() == 0) continue;
      }
    }
  }
}

void MainWindow::coalescenceAntiHelium3() {}

void MainWindow::coalescenceHypertriton() {}

void MainWindow::coalescenceAntiHypertriton() {}
