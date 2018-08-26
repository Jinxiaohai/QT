#ifndef TRACK_H
#define TRACK_H

#include "TLorentzVector.h"

struct Track {
  Track(int ID = 0, double Px = 0., double Py = 0., double Pz = 0.,
        double Energy = 0., double X = 0., double Y = 0, double Z = 0.,
        double Time = 0.);

  int ID;
  TLorentzVector momentum;
  TLorentzVector coordinate;
  int flag;
};

#endif  // TRACK_H
