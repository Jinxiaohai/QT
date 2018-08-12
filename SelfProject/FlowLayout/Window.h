#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

QT_BEGIN_NAMESPACE
class QLable;
QT_END_NAMESPACE

class Window : public QWidget {
  Q_OBJECT
 public:
  explicit Window(QWidget *parent = nullptr);

 signals:

 public slots:
};

#endif  // WINDOW_H
