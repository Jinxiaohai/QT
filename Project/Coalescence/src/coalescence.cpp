#include "TH1D.h"

#include "AMPT.h"
#include "coalescence.h"
#include "jglobal.h"

Coalescence::Coalescence(QObject* parent) : QObject(parent) {}

void Coalescence::getEventData(const AMPT*& ampt) {
  double Energy = 0.;
  for (int i = 0; i != ampt->Event_multi; ++i) {
    Energy = static_cast<double>(
        std::sqrt(ampt->Px[i] * ampt->Px[i] + ampt->Py[i] * ampt->Py[i] +
                  ampt->Pz[i] * ampt->Pz[i] + ampt->Mass[i] * ampt->Mass[i]));
    switch (ampt->ID[i]) {
      case 2212: {
        Track tmpTrack(
            ampt->ID[i], static_cast<double>(ampt->Px[i]),
            static_cast<double>(ampt->Py[i]), static_cast<double>(ampt->Pz[i]),
            static_cast<double>(Energy), static_cast<double>(ampt->X[i]),
            static_cast<double>(ampt->Y[i]), static_cast<double>(ampt->Z[i]),
            static_cast<double>(ampt->Time[i]));
        protonTracks.push_back(tmpTrack);
        break;
      }
      case -2212: {
        Track tmpTrack(
            ampt->ID[i], static_cast<double>(ampt->Px[i]),
            static_cast<double>(ampt->Py[i]), static_cast<double>(ampt->Pz[i]),
            static_cast<double>(Energy), static_cast<double>(ampt->X[i]),
            static_cast<double>(ampt->Y[i]), static_cast<double>(ampt->Z[i]),
            static_cast<double>(ampt->Time[i]));
        antiProtonTracks.push_back(tmpTrack);
        break;
      }
      case 2112: {
        Track tmpTrack(
            ampt->ID[i], static_cast<double>(ampt->Px[i]),
            static_cast<double>(ampt->Py[i]), static_cast<double>(ampt->Pz[i]),
            static_cast<double>(Energy), static_cast<double>(ampt->X[i]),
            static_cast<double>(ampt->Y[i]), static_cast<double>(ampt->Z[i]),
            static_cast<double>(ampt->Time[i]));
        neutronTracks.push_back(tmpTrack);
        break;
      }
      case -2112: {
        Track tmpTrack(
            ampt->ID[i], static_cast<double>(ampt->Px[i]),
            static_cast<double>(ampt->Py[i]), static_cast<double>(ampt->Pz[i]),
            static_cast<double>(Energy), static_cast<double>(ampt->X[i]),
            static_cast<double>(ampt->Y[i]), static_cast<double>(ampt->Z[i]),
            static_cast<double>(ampt->Time[i]));
        antiNeutronTracks.push_back(tmpTrack);
        break;
      }
      case 3122: {
        Track tmpTrack(
            ampt->ID[i], static_cast<double>(ampt->Px[i]),
            static_cast<double>(ampt->Py[i]), static_cast<double>(ampt->Pz[i]),
            static_cast<double>(Energy), static_cast<double>(ampt->X[i]),
            static_cast<double>(ampt->Y[i]), static_cast<double>(ampt->Z[i]),
            static_cast<double>(ampt->Time[i]));
        lambdaTracks.push_back(tmpTrack);
        break;
      }
      case -3122: {
        Track tmpTrack(
            ampt->ID[i], static_cast<double>(ampt->Px[i]),
            static_cast<double>(ampt->Py[i]), static_cast<double>(ampt->Pz[i]),
            static_cast<double>(Energy), static_cast<double>(ampt->X[i]),
            static_cast<double>(ampt->Y[i]), static_cast<double>(ampt->Z[i]),
            static_cast<double>(ampt->Time[i]));
        antiLambdaTracks.push_back(tmpTrack);
        break;
      }
      default:
        break;
    }
  }
}

void Coalescence::coalescenceHelium3() {
  if (protonTracks.size() * neutronTracks.size() == 0) {
    return;
  }

  for (size_t i = 0; i != protonTracks.size(); ++i) {
    if (protonTracks.size() == 0) continue;
    for (size_t j = i; j != protonTracks.size(); ++j) {
      for (size_t k = 0; k != neutronTracks.size(); ++k) {
        if (neutronTracks.size() == 0) continue;
        TLorentzVector firstProton = protonTracks[i].momentum;
        TLorentzVector secondProton = protonTracks[j].momentum;
        TLorentzVector neutron = neutronTracks[k].momentum;

        if ((firstProton - secondProton).P() > pDiffCutHelium3) continue;
        if ((firstProton - neutron).P() > pDiffCutHelium3) continue;
        if ((secondProton - neutron).P() > pDiffCutHelium3) continue;

        double totalEnergy =
            firstProton.Energy() + secondProton.Energy() + neutron.Energy();
        TVector3 totalMomentum =
            firstProton.Vect() + secondProton.Vect() + secondProton.Vect();
        double resetEnergy =
            sqrt(totalMomentum.Mag2() +
                 helium3AndAntiHelium3Mass * helium3AndAntiHelium3Mass);
        double deltaEnergy = totalEnergy - resetEnergy;

        TLorentzVector helium3LorentzVector;
        helium3LorentzVector.SetVect(totalMomentum);
        helium3LorentzVector.SetE(resetEnergy);

        helium3dNdy->Fill(helium3LorentzVector.Rapidity(), 1. / 0.5);
        helium3dNdydPt->Fill(
            helium3LorentzVector.Pt(),
            1. / (2 * TMath::Pi() * helium3LorentzVector.Pt() * 1. * 0.5));
      }
    }
  }
}
