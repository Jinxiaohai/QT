#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QEventLoop>
#include <QGLWidget>
#include <QList>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

enum GestureDirect { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

enum AnimationType { MOVE = 0, APPEARANCE = 1 };

struct Animation {
  AnimationType type;
  GestureDirect direct;
  QPointF startPos;
  QPointF endPos;
  int digit;
  int digit2;
};

class GameWidget : public QGLWidget {
  Q_OBJECT
 public:
  explicit GameWidget(QWidget *parent = 0);

 private:
  int board[4][4];
  int digitCount;
  int score;
  QPoint startPos;
  QList<Animation> animationList;
  qreal w, h;
  qreal ratioW, ratioH;
  qreal rX, rY;
  bool isAnimating;
  QTimer timer;

  void init2Block();
  bool checkGameOver();
  bool checkWin();
  int getBitCount(int);
  bool playAnimation(Animation &, QPainter &);
  bool drawAnimation(QPainter &);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);

 signals:
  void GestureMove(GestureDirect);
  void ScoreInc(int);
  void GameOver();
  void win();

 public slots:
  void onGestureMove(GestureDirect);
  void restart();
};

#endif
