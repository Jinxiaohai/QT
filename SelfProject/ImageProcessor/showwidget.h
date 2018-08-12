#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

QT_BEGIN_NAMESPACE
class QImage;
class QLabel;
class QTextEdit;
QT_END_NAMESPACE

class ShowWidget : public QWidget {
  Q_OBJECT
 public:
  explicit ShowWidget(QWidget *parent = nullptr);
  QImage img;
  QLabel *imageLabel;
  QTextEdit *text;

 signals:

 public slots:
};

#endif  // SHOWWIDGET_H
