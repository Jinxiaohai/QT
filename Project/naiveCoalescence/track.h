#ifndef TRACK_H
#define TRACK_H

#include <TLorentzVector.h>

class Track {
 public:
  static void dealMomentum(float srcPx, float srcPy, float srcPz, float srcMass, float srcX, float srcY, float srcZ,
                           float srcTime, double &desPx, double &desPy, double &desPz, double &desEnergy, double &desX,
                           double &desY, double &desZ, double &desTime);

  Track(int PID = 0, double Px = 0., double Py = 0., double Pz = 0., double Energy = 0., double X = 0., double Y = 0.,
        double Z = 0., double Time = 0., int flag = 1);

  int getPID() const;
  void setPID(int value);

  TLorentzVector getMomentum() const;
  void setMomentum(const TLorentzVector &value);

  TLorentzVector getCoordinate() const;
  void setCoordinate(const TLorentzVector &value);

  int getFlag() const;
  void setFlag(int value);

 private:
  int PID;
  TLorentzVector momentum;
  TLorentzVector coordinate;
  int flag;
};

#endif  // TRACK_H
