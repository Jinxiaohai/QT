#ifndef COALESCENCE_H
#define COALESCENCE_H

#include <QObject>
#include <QVector>

#include "track.h"

class AMPT;

class Coalescence : public QObject {
  Q_OBJECT
 public:
  explicit Coalescence(QObject *parent = nullptr);

  void getEventData(const AMPT *&ampt);
  void coalescenceHelium3();
  void coalescenceAntiHelium3();
  void coalescenceHypertriton();
  void coalescenceAntiHypertriton();

 signals:

 public slots:

 private:
  QVector<Track> protonTracks;
  QVector<Track> antiProtonTracks;
  QVector<Track> neutronTracks;
  QVector<Track> antiNeutronTracks;
  QVector<Track> lambdaTracks;
  QVector<Track> antiLambdaTracks;

  double pDiffCutHelium3;
  double helium3AndAntiHelium3Mass;
  double hypertritonAndHypertritonMass;
  double centralityLow;
  double centralityHigh;
  double rapidityLow;
  double rapidityHigh;
};

#endif  // COALESCENCE_H
