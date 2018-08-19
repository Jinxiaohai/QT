#include "GameWidget.h"

QColor digitBkg[11] = {
    QColor::fromRgb(0xFF, 0xFF, 0xCC), QColor::fromRgb(0xFF, 0xFF, 0x99),
    QColor::fromRgb(0xFF, 0xCC, 0xCC), QColor::fromRgb(0xFF, 0xCC, 0x99),
    QColor::fromRgb(0xFF, 0x99, 0x99), QColor::fromRgb(0xFF, 0x99, 0x66),
    QColor::fromRgb(0xFF, 0x66, 0x66), QColor::fromRgb(0xCC, 0x99, 0x66),
    QColor::fromRgb(0xCC, 0x33, 0x33), QColor::fromRgb(0xCC, 0x00, 0x33),
    QColor::fromRgb(0xFF, 0x00, 0x00)};

QPointF dPos[5];

GameWidget::GameWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), timer(this) {
  connect(this, SIGNAL(GestureMove(GestureDirect)),
          SLOT(onGestureMove(GestureDirect)));
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  memset(board, 0, sizeof(board));
  score = 0;
  digitCount = 2;
  isAnimating = false;
  init2Block();
}

void GameWidget::init2Block() {
  board[rand() % 4][rand() % 4] = 2;
  int i = rand() % 4, j = rand() % 4;
  while (board[i][j] != 0) i = rand() % 4, j = rand() % 4;
  board[i][j] = 2;
  update();
}

void GameWidget::mousePressEvent(QMouseEvent *e) { startPos = e->pos(); }

void GameWidget::mouseReleaseEvent(QMouseEvent *e) {
  if (isAnimating) return;
  float dX = (float)(e->pos().x() - startPos.x());
  float dY = (float)(e->pos().y() - startPos.y());
  if (abs(dX) > abs(dY)) {
    if (dX < 0)
      emit GestureMove(LEFT);
    else
      emit GestureMove(RIGHT);
  } else {
    if (dY < 0)
      emit GestureMove(UP);
    else
      emit GestureMove(DOWN);
  }
}

void GameWidget::onGestureMove(GestureDirect direct) {
  int i, j, k;
  Animation a;
  bool move = false, combine = false;
  bool isCombined[4][4];
  memset(isCombined, 0, sizeof(isCombined));
  switch (direct) {
    case LEFT:
      for (i = 0; i < 4; i++) {
        j = 0, k = 0;
        while (true) {
          while (j < 4 && board[i][j] == 0) j++;
          if (j > 3) break;
          qSwap(board[i][k], board[i][j]);
          if (j != k) move = true;
          a.type = MOVE;
          a.startPos = QPointF(7 * ratioW + (w + 5 * ratioW) * j,
                               7 * ratioH + (h + 5 * ratioH) * i);
          a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * k,
                             7 * ratioH + (h + 5 * ratioH) * i);
          a.digit = a.digit2 = board[i][k];
          a.direct = LEFT;
          if (k > 0 && board[i][k] == board[i][k - 1] &&
              !isCombined[i][k - 1]) {
            board[i][k - 1] <<= 1;
            isCombined[i][k - 1] = true;
            board[i][k] = 0;
            combine = true;
            a.digit2 = board[i][k - 1];
            a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * (k - 1),
                               7 * ratioH + (h + 5 * ratioH) * i);
            score += board[i][k - 1];
            emit ScoreInc(score);
            digitCount--;
          } else
            k++;
          j++;
          animationList.append(a);
        }
      }
      break;
    case RIGHT:
      for (i = 0; i < 4; i++) {
        j = 3, k = 3;
        while (true) {
          while (j > -1 && board[i][j] == 0) j--;
          if (j < 0) break;
          qSwap(board[i][k], board[i][j]);
          if (j != k) move = true;
          a.type = MOVE;
          a.startPos = QPointF(7 * ratioW + (w + 5 * ratioW) * j,
                               7 * ratioH + (h + 5 * ratioH) * i);
          a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * k,
                             7 * ratioH + (h + 5 * ratioH) * i);
          a.digit = a.digit2 = board[i][k];
          a.direct = RIGHT;
          if (k < 3 && board[i][k] == board[i][k + 1] &&
              !isCombined[i][k + 1]) {
            board[i][k + 1] <<= 1;
            isCombined[i][k + 1] = true;
            board[i][k] = 0;
            combine = true;
            a.digit2 = board[i][k + 1];
            a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * (k + 1),
                               7 * ratioH + (h + 5 * ratioH) * i);
            score += board[i][k + 1];
            emit ScoreInc(score);
            digitCount--;
          } else
            k--;
          j--;
          animationList.append(a);
        }
      }
      break;
    case UP:
      for (i = 0; i < 4; i++) {
        j = 0, k = 0;
        while (true) {
          while (j < 4 && board[j][i] == 0) j++;
          if (j > 3) break;
          qSwap(board[k][i], board[j][i]);
          if (j != k) move = true;
          a.type = MOVE;
          a.startPos = QPointF(7 * ratioW + (w + 5 * ratioW) * i,
                               7 * ratioH + (h + 5 * ratioH) * j);
          a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * i,
                             7 * ratioH + (h + 5 * ratioH) * k);
          a.digit = a.digit2 = board[k][i];
          a.direct = UP;
          if (k > 0 && board[k][i] == board[k - 1][i] &&
              !isCombined[k - 1][i]) {
            board[k - 1][i] <<= 1;
            isCombined[k - 1][i] = true;
            board[k][i] = 0;
            combine = true;
            a.digit2 = board[k - 1][i];
            a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * i,
                               7 * ratioH + (h + 5 * ratioH) * (k - 1));
            score += board[k - 1][i];
            emit ScoreInc(score);
            digitCount--;
          } else
            k++;
          j++;
          animationList.append(a);
        }
      }
      break;
    case DOWN:
      for (i = 0; i < 4; i++) {
        j = 3, k = 3;
        while (true) {
          while (j > -1 && board[j][i] == 0) j--;
          if (j < 0) break;
          qSwap(board[k][i], board[j][i]);
          if (j != k) move = true;
          a.type = MOVE;
          a.startPos = QPointF(7 * ratioW + (w + 5 * ratioW) * i,
                               7 * ratioH + (h + 5 * ratioH) * j);
          a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * i,
                             7 * ratioH + (h + 5 * ratioH) * k);
          a.digit = a.digit2 = board[k][i];
          a.direct = DOWN;
          if (k < 3 && board[k][i] == board[k + 1][i] &&
              !isCombined[k + 1][i]) {
            board[k + 1][i] <<= 1;
            isCombined[k + 1][i] = true;
            board[k][i] = 0;
            combine = true;
            a.digit2 = board[k + 1][i];
            a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * i,
                               7 * ratioH + (h + 5 * ratioH) * (k + 1));
            score += board[k + 1][i];
            emit ScoreInc(score);
            digitCount--;
          } else
            k--;
          j--;
          animationList.append(a);
        }
      }
      break;
  }

  if ((move || combine) && digitCount != 16) {
    i = rand() % 4, j = rand() % 4;
    while (board[i][j] != 0) i = rand() % 4, j = rand() % 4;
    board[i][j] = (rand() % 2 + 1) * 2;
    a.type = APPEARANCE;
    a.startPos = a.endPos = QPointF(7 * ratioW + (w + 5 * ratioW) * j,
                                    7 * ratioH + (h + 5 * ratioH) * i);
    a.startPos += QPointF(w / 2, h / 2);
    a.digit = board[i][j];
    animationList.append(a);
    digitCount++;
  }

  isAnimating = true;

  timer.start(10);
}

bool GameWidget::drawAnimation(QPainter &painter) {
  QList<Animation>::iterator it;

  QFont font;
  font.setFamily("Consolas");
  font.setBold(true);
  font.setPixelSize(40 * ratioH);
  painter.setFont(font);

  bool ok = true;

  QBrush brush(QColor::fromRgb(141, 121, 81));
  painter.setBrush(brush);

  painter.setPen(Qt::NoPen);

  painter.drawRoundedRect(QRectF(2 * ratioW, 2 * ratioH, width() - 4 * ratioW,
                                 height() - 4 * ratioH),
                          rX, rY);

  brush.setColor(QColor::fromRgb(171, 165, 141));
  painter.setBrush(brush);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      painter.drawRoundedRect(QRectF(7 * ratioW + (w + 5 * ratioW) * j,
                                     7 * ratioH + (h + 5 * ratioH) * i, w, h),
                              rX, rY);

  for (it = animationList.begin(); it != animationList.end(); it++)
    if (!playAnimation(*it, painter)) ok = false;

  return ok;
}

bool GameWidget::playAnimation(Animation &a, QPainter &painter) {
  bool rtn = false;

  QBrush brush(Qt::SolidPattern);

  if (a.type == MOVE) {
    switch (a.direct) {
      case LEFT:
        if (a.startPos.x() > a.endPos.x())
          a.startPos += dPos[LEFT];
        else
          a.startPos = a.endPos, rtn = true;
        break;
      case RIGHT:
        if (a.startPos.x() < a.endPos.x())
          a.startPos += dPos[RIGHT];
        else
          a.startPos = a.endPos, rtn = true;
        break;
      case UP:
        if (a.startPos.y() > a.endPos.y())
          a.startPos += dPos[UP];
        else
          a.startPos = a.endPos, rtn = true;
        break;
      case DOWN:
        if (a.startPos.y() < a.endPos.y())
          a.startPos += dPos[DOWN];
        else
          a.startPos = a.endPos, rtn = true;
    }
    if (!rtn) {
      brush.setColor(digitBkg[getBitCount(a.digit)]);
      painter.setBrush(brush);
      painter.drawRoundedRect(QRectF(a.startPos.x(), a.startPos.y(), w, h), rX,
                              rY);
      painter.setPen(QColor::fromRgb(0, 0, 0));
      painter.drawText(QRectF(a.startPos.x(), a.startPos.y(), w, h),
                       Qt::AlignCenter, QString::number(a.digit));
    } else {
      brush.setColor(digitBkg[getBitCount(a.digit2)]);
      painter.setBrush(brush);
      painter.drawRoundedRect(QRectF(a.startPos.x(), a.startPos.y(), w, h), rX,
                              rY);
      painter.setPen(QColor::fromRgb(0, 0, 0));
      painter.drawText(QRectF(a.startPos.x(), a.startPos.y(), w, h),
                       Qt::AlignCenter, QString::number(a.digit2));
    }
    painter.setPen(Qt::NoPen);
  } else {
    if (a.startPos.x() > a.endPos.x())
      a.startPos += dPos[4];
    else
      a.startPos = a.endPos, rtn = true;
    brush.setColor(digitBkg[getBitCount(a.digit)]);
    painter.setBrush(brush);
    painter.drawRoundedRect(QRectF(a.startPos.x(), a.startPos.y(),
                                   w - 2 * (a.startPos.x() - a.endPos.x()),
                                   h - 2 * (a.startPos.y() - a.endPos.y())),
                            rX, rY);
    painter.setPen(QColor::fromRgb(0, 0, 0));
    painter.drawText(QRectF(a.endPos.x(), a.endPos.y(), w, h), Qt::AlignCenter,
                     QString::number(a.digit));
    painter.setPen(Qt::NoPen);
  }
  return rtn;
}

void GameWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);

  if (isAnimating) {
    if (drawAnimation(painter)) {
      isAnimating = false;
      timer.stop();
      animationList.clear();
      if (digitCount == 16) {
        if (checkGameOver()) emit GameOver();
      }
      if (checkWin()) emit win();
    }
    return;
  }

  QBrush brush(QColor::fromRgb(141, 121, 81));
  painter.setBrush(brush);

  painter.setPen(Qt::NoPen);

  painter.drawRoundedRect(QRectF(2 * ratioW, 2 * ratioH, width() - 4 * ratioW,
                                 height() - 4 * ratioH),
                          rX, rY);

  QFont font;
  font.setFamily("Consolas");
  font.setBold(true);
  font.setPixelSize(40 * ratioH);
  painter.setFont(font);

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (board[i][j]) {
        brush.setColor(digitBkg[getBitCount(board[i][j])]);
        painter.setBrush(brush);
        painter.drawRoundedRect(QRectF(7 * ratioW + (w + 5 * ratioW) * j,
                                       7 * ratioH + (h + 5 * ratioH) * i, w, h),
                                rX, rY);
        painter.setPen(QColor::fromRgb(0, 0, 0));
        painter.drawText(QRectF(7 * ratioW + (w + 5 * ratioW) * j,
                                7 * ratioH + (h + 5 * ratioH) * i, w, h),
                         Qt::AlignCenter, QString::number(board[i][j]));
        painter.setPen(Qt::NoPen);
      } else {
        brush.setColor(QColor::fromRgb(171, 165, 141));
        painter.setBrush(brush);
        painter.drawRoundedRect(QRectF(7 * ratioW + (w + 5 * ratioW) * j,
                                       7 * ratioH + (h + 5 * ratioH) * i, w, h),
                                rX, rY);
      }
    }
}

void GameWidget::resizeEvent(QResizeEvent *) {
  ratioW = width() / 400.0, ratioH = height() / 400.0;
  w = width() - 4 * ratioW, h = height() - 4 * ratioH;
  w = (w - 25 * ratioW) / 4, h = (h - 25 * ratioH) / 4;
  rX = 15 * ratioW, rY = 15 * ratioH;
  dPos[0] = QPointF(-25 * ratioW, 0);
  dPos[1] = QPointF(25 * ratioW, 0);
  dPos[2] = QPointF(0, -25 * ratioH);
  dPos[3] = QPointF(0, 25 * ratioH);
  dPos[4] = QPointF(-4 * ratioW, -4 * ratioH);
}

void GameWidget::restart() {
  score = 0;
  digitCount = 2;
  memset(board, 0, sizeof(board));
  init2Block();
  emit ScoreInc(score);
  update();
}

bool GameWidget::checkGameOver() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (j != 3 && board[i][j] == board[i][j + 1]) return false;
      if (i != 3 && board[i][j] == board[i + 1][j]) return false;
    }
  return true;
}

bool GameWidget::checkWin() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (board[i][j] == 2048) return true;
  return false;
}

int GameWidget::getBitCount(int n) {
  int c = 0;
  while (n >>= 1) c++;
  return c - 1;
}
