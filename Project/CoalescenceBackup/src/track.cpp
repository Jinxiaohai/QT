#include "track.h"

/*!
 * \brief Track::dealMomentum
 * \param srcPx
 * \param srcPy
 * \param srcPz
 * \param srcMass
 * \param desPx
 * \param desPy
 * \param desPz
 * \param desEnergy
 */
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

/*!
 * \brief Track::Track
 * \param PID
 * \param Px
 * \param Py
 * \param Pz
 * \param Energy
 * \param X
 * \param Y
 * \param Z
 * \param Time
 * \param flag
 */
Track::Track(int PID, double Px, double Py, double Pz, double Energy, double X, double Y, double Z, double Time,
             int flag)
    : momentum(Px, Py, Pz, Energy), coordinate(X, Y, Z, Time) {
  this->PID = PID;
  this->flag = flag;
}

inline int Track::getPID() const { return this->PID; }

TLorentzVector Track::getMomentum() const { return this->momentum; }

TLorentzVector Track::getCoordinate() const { return this->coordinate; }

int Track::getFlag() { return this->flag; }

void Track::setPID(int PID) { this->PID = PID; }

void Track::setMomentum(TLorentzVector &momentum) { this->momentum = momentum; }

void Track::setCoordinate(TLorentzVector &coordinate) { this->coordinate = coordinate; }

void Track::setFlag(int flag) { this->flag = flag; }
