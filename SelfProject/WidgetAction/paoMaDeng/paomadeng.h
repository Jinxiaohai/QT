#ifndef PAOMADENG_H
#define PAOMADENG_H

#include <QWidget>

class PaoMaDeng : public QWidget {
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText)

 public:
  PaoMaDeng(QWidget *parent = 0);
  ~PaoMaDeng();

  void setText(const QString &newText);
  QString text() const { return myText; }
  QSize sizeHint() const;

 protected:
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);
  void showEvent(QShowEvent *event);
  void hideEvent(QHideEvent *event);

 private:
  QString myText;
  int offset;
  int myTimerId;
};

#endif  // PAOMADENG_H
