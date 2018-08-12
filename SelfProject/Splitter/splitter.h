#ifndef SPLITTER_H
#define SPLITTER_H

#include <QWidget>

class Splitter : public QWidget
{
  Q_OBJECT

public:
  Splitter(QWidget *parent = 0);
  ~Splitter();
};

#endif // SPLITTER_H
