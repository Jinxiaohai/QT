#include "TChain.h"
#include "TLorentzRotation.h"

#include "AMPT.h"
#include "coalescence.h"
#include "track.h"

Coalescence::Coalescence(QObject *parent) : QObject(parent) {}

Coalescence::Coalescence(double PIDMass, double pDiffCut, double ptLow, double ptHigh, double rapidityLow, double rapidityHigh, int centralityLow,
                         int centralityHigh, QObject *parent)
    : QObject(parent) {
  this->PIDMass = PIDMass;
  this->pDiffCut = pDiffCut;
  this->ptLow = ptLow;
  this->ptHigh = ptHigh;
  this->rapidityLow = rapidityLow;
  this->rapidityHigh = rapidityHigh;
  this->centralityLow = centralityLow;
  this->centralityHigh = centralityHigh;
}

void Coalescence::getpnl(TChain *&chain, long int entry) {
  AMPT ampt(chain);
  chain->GetEntry(entry);

  protonTracks.clear();
  antiProtonTracks.clear();
  neutronTracks.clear();
  antiNeutronTracks.clear();
  lambdaTracks.clear();
  antiLambdaTracks.clear();

  int multiTracks = ampt.Event_multi;
  int PID = 0;
  double Px = 0., Py = 0., Pz = 0., Energy = 0.;
  double X = 0., Y = 0., Z = 0., Time = 0.;

  for (int i = 0; i != multiTracks; ++i) {
    PID = ampt.ID[i];
    Track::dealMomentum(ampt.Px[i], ampt.Py[i], ampt.Pz[i], ampt.Mass[i], ampt.X[i], ampt.Y[i], ampt.Z[i], ampt.Time[i], Px, Py, Pz, Energy, X, Y, Z,
                        Time);
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

void Coalescence::generateParticle(Coalescence::PARTICLETYPE type) {}

void Coalescence::generateHelium3AndAntiHelium3(QVector<Track> &proton, QVector<Track> &neutron) {
  double labTotalEnergy;
  TVector3 labTotalMomentum;
  double resetEnergy;
  TVector3 betaLabToCMS;

  TLorentzVector cluterInformation;

  TLorentzVector protonCMS1;
  TLorentzVector protonCMS2;
  TLorentzVector neutronCMS1;

  for (int p1 = 0; p1 != proton.size(); ++p1) {
    if (proton[p1].getFlag() == 0) continue;
    for (int p2 = p1; p2 != proton.size(); ++p2) {
      if (proton[p2].getFlag() == 0) continue;
      for (int n1 = 0; n1 != neutron.size(); ++n1) {
        if (neutron[n1].getFlag() == 0) continue;
        labTotalEnergy = proton[p1].getMomentum().Energy() + proton[p2].getMomentum().Energy() + neutron[n1].getMomentum().Energy();
        labTotalMomentum = proton[p1].getMomentum().Vect() + proton[p2].getMomentum().Vect() + neutron[n1].getMomentum().Vect();
        resetEnergy = sqrt(labTotalMomentum.Mag2() + PIDMass * PIDMass);

        betaLabToCMS = (-1. / labTotalEnergy) * labTotalMomentum;
        TLorentzRotation rotation(betaLabToCMS);

        protonCMS1 = rotation * proton[p1].getMomentum();
        protonCMS2 = rotation * proton[p2].getMomentum();
        neutronCMS1 = rotation * neutron[n1].getMomentum();

        if ((protonCMS1.Vect() - protonCMS2.Vect()).Mag() > 0.08) continue;
        if ((protonCMS1.Vect() - neutronCMS1.Vect()).Mag() > 0.08) continue;
        if ((protonCMS2.Vect() - neutronCMS1.Vect()).Mag() > 0.08) continue;

        cluterInformation.SetE(resetEnergy);
        cluterInformation.SetVect(labTotalMomentum);

        if (cluterInformation.Rapidity() > this->rapidityHigh || cluterInformation.Rapidity() < this->rapidityLow) continue;
        if (cluterInformation.Pt() > this->ptHigh || cluterInformation.Pt() < this->ptLow) continue;

        proton[p1].setFlag(0);
        proton[p2].setFlag(0);
        neutron[n1].setFlag(0);
      }
    }
  }
}

void Coalescence::generateHypertritonAndAntiHypertriton(QVector<Track> &proton, QVector<Track> &neutron, QVector<Track> &lambda) {
  double labTotalEnergy;
  TVector3 labTotalMomentum;
  double resetEnergy;
  TVector3 betaLabToCMS;

  TLorentzVector cluterInformation;

  TLorentzVector protonCMS1;
  TLorentzVector neutronCMS1;
  TLorentzVector lambdaCMS1;

  for (int p1 = 0; p1 != proton.size(); ++p1) {
    if (proton[p1].getFlag() == 0) continue;

    for (int n1 = 0; n1 != neutron.size(); ++n1) {
      if (neutron[n1].getFlag() == 0) continue;

      for (int l1 = 0; l1 != lambda.size(); ++l1) {
        if (lambda[l1].getFlag() == 0) continue;

        labTotalEnergy = proton[p1].getMomentum().Energy() + neutron[n1].getMomentum().Energy() + lambda[l1].getMomentum().Energy();
        labTotalMomentum = proton[p1].getMomentum().Vect() + neutron[n1].getMomentum().Vect() + lambda[l1].getMomentum().Vect();
        resetEnergy = sqrt(labTotalMomentum.Mag2() + PIDMass * PIDMass);

        betaLabToCMS = (-1. / labTotalEnergy) * labTotalMomentum;
        TLorentzRotation rotation(betaLabToCMS);

        protonCMS1 = rotation * proton[p1].getMomentum();
        neutronCMS1 = rotation * neutron[n1].getMomentum();
        lambdaCMS1 = rotation * lambda[l1].getMomentum();

        if ((protonCMS1.Vect() - neutronCMS1.Vect()).Mag() > 0.08) continue;
        if ((protonCMS1.Vect() - lambdaCMS1.Vect()).Mag() > 0.08) continue;
        if ((neutronCMS1.Vect() - lambdaCMS1.Vect()).Mag() > 0.08) continue;

        cluterInformation.SetE(resetEnergy);
        cluterInformation.SetVect(labTotalMomentum);

        if (cluterInformation.Rapidity() > this->rapidityHigh || cluterInformation.Rapidity() < this->rapidityLow) continue;
        if (cluterInformation.Pt() > this->ptHigh || cluterInformation.Pt() < this->ptLow) continue;

        proton[p1].setFlag(0);
        neutron[n1].setFlag(0);
        lambda[l1].setFlag(0);
      }
    }
  }
}

bool Coalescence::overWriteMass(const QString &text) {
  bool ok;
  this->PIDMass = text.toDouble(&ok);
  return ok;
}

bool Coalescence::overWritepDiffCut(const QString &text) {
  bool ok;
  this->pDiffCut = text.toDouble(&ok);
  return ok;
}

void Coalescence::overWritePtLow(double value) { this->ptLow = value; }

void Coalescence::overWritePtHigh(double value) { this->ptHigh = value; }

void Coalescence::overWriteRapidityLow(double value) { this->rapidityLow = value; }

void Coalescence::overWriteRapidityHigh(double value) { this->rapidityHigh = value; }

void Coalescence::overWriteCentralityLow(int value) { this->centralityLow = value; }

void Coalescence::overWriteCentralityHigh(int value) { this->centralityHigh = value; }
