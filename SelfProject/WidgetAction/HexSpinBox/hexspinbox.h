#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QtCore/qglobal.h>
#include <QSpinBox>

class HexSpinBox : public QSpinBox {
  Q_OBJECT

 public:
  HexSpinBox();

 protected:
  QValidator::State validata(QString &text, int &pos) const;
  int valueFromText(const QString &text) const;
  QString textFromValue(int value) const;

 private:
  QRegExpValidator *validator;
};

#endif  // HEXSPINBOX_H
