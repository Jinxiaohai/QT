#include "track.h"

void Track::dealMomentum(float srcPx, float srcPy, float srcPz, float srcMass, float srcX, float srcY, float srcZ,
                         float srcTime, double &desPx, double &desPy, double &desPz, double &desEnergy, double &desX,
                         double &desY, double &desZ, double &desTime) {
  desPx = static_cast<double>(srcPx);
  desPy = static_cast<double>(srcPy);
  desPz = static_cast<double>(srcPz);
  desEnergy = sqrt(desPx * desPx + desPy * desPy + desPz * desPz + srcMass * srcMass);
  desX = static_cast<double>(srcX);
  desY = static_cast<double>(srcY);
  desZ = static_cast<double>(srcZ);
  desTime = static_cast<double>(srcTime);
}

Track::Track(int PID, double Px, double Py, double Pz, double Energy,  //
             double X, double Y, double Z, double Time, int flag)
    : momentum(Px, Py, Pz, Energy), coordinate(X, Y, Z, Time) {
  this->PID = PID;
  this->flag = flag;
}

int Track::getPID() const { return PID; }

void Track::setPID(int value) { PID = value; }

TLorentzVector Track::getMomentum() const { return momentum; }

void Track::setMomentum(const TLorentzVector &value) { momentum = value; }

TLorentzVector Track::getCoordinate() const { return coordinate; }

void Track::setCoordinate(const TLorentzVector &value) { coordinate = value; }

int Track::getFlag() const { return flag; }

void Track::setFlag(int value) { flag = value; }
