#ifndef TRACK_H
#define TRACK_H

#include "TLorentzVector.h"

class Track {
 public:
  static void dealMomentum(float srcPx, float srcPy, float srcPz, float srcMass, float srcX, float srcY, float srcZ,
                           float srcTime, double &desPx, double &desPy, double &desPz, double &desEnergy, double &desX,
                           double &desY, double &desZ, double &desTime);

  Track(int PID = 0, double Px = 0., double Py = 0., double Pz = 0., double Energy = 0., double X = 0., double Y = 0,
        double Z = 0., double Time = 0., int flag = 0);

  // get function
  int getPID() const;
  TLorentzVector getMomentum() const;
  TLorentzVector getCoordinate() const;
  int getFlag();

  // set function
  void setPID(int PID);
  void setMomentum(TLorentzVector &momentum);
  void setCoordinate(TLorentzVector &coordinate);
  void setFlag(int flag);

 private:
  int PID;
  TLorentzVector momentum;
  TLorentzVector coordinate;
  int flag;
};

#endif  // TRACK_H
