#include "TLorentzVector.h"

#include "track.h"

Track::Track(int ID, double Px, double Py, double Pz, double Energy, double X,
             double Y, double Z, double Time)
    : momentum(Px, Py, Pz, Energy), coordinate(X, Y, Z, Time) {
  this->ID = ID;
  this->flag = 1;
}
