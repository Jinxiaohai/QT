#ifndef WIDGET_H
#define WIDGET_H

#include <QFile>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include "GameWidget.h"

#define LBLSTYLESHEET                                             \
  "QLabel {color: orange;background: #FFFFCC;border: %1px solid " \
  "orange;border-radius: %2px;}"
#define BTNSTYLESHEET                                                 \
  "QPushButton {color: red;background: lightgray;border: %1px solid " \
  "darkgray;border-radius: %2px;} QPushButton:pressed{color: "        \
  "white;background: orange;border: %1px solid darkgray;border-radius: %2px;}"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = 0);
  ~Widget();

 private:
  QPushButton *restartBtn;
  QLabel *scoreLbl;
  QLabel *highScoreLbl;
  GameWidget *gameWidget;
  qreal ratioW, ratioH;
  int highScore;

 protected:
  void resizeEvent(QResizeEvent *);

 public slots:
  void onScoreInc(int);
  void onGameOver();
  void onWin();
};

#endif  // WIDGET_H
