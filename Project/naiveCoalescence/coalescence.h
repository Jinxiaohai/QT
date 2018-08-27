#ifndef COALESCENCE_H
#define COALESCENCE_H

#include <qglobal.h>
#include <QObject>
#include <QVector>

#include "AMPT.h"
#include "track.h"

class TChain;

class Coalescence : public QObject {
  Q_OBJECT
 public:
  enum PARTICLETYPE { Helium3 = 0, AntiHelium3 = 1, Hypertriton = 2, AntiHypertriton = 3 };

  explicit Coalescence(QObject *parent = nullptr);
  Coalescence(double PIDMass = 0., double pDiffCut = 0., double ptLow = 0., double ptHigh = 0., double rapidityLow = 0., double rapidityHigh = 0.,
              int centralityLow = 0, int centralityHigh = 0, QObject *parent = nullptr);

  void getpnl(TChain *&chain, long int entry);

  void generateParticle(PARTICLETYPE type);
  void generateHelium3AndAntiHelium3(QVector<Track> &proton, QVector<Track> &neutron);
  void generateHypertritonAndAntiHypertriton(QVector<Track> &proton, QVector<Track> &neutron, QVector<Track> &lambda);

 signals:

 public slots:
  bool overWriteMass(const QString &text);
  bool overWritepDiffCut(const QString &text);
  void overWritePtLow(double value);
  void overWritePtHigh(double value);
  void overWriteRapidityLow(double value);
  void overWriteRapidityHigh(double value);
  void overWriteCentralityLow(int value);
  void overWriteCentralityHigh(int value);

 private:
  double PIDMass;
  double pDiffCut;
  double ptLow;
  double ptHigh;
  double rapidityLow;
  double rapidityHigh;
  double centralityLow;
  double centralityHigh;

  TChain *chain;

  QVector<Track> protonTracks;
  QVector<Track> antiProtonTracks;
  QVector<Track> neutronTracks;
  QVector<Track> antiNeutronTracks;
  QVector<Track> lambdaTracks;
  QVector<Track> antiLambdaTracks;
};

#endif  // COALESCENCE_H
