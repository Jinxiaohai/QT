#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QTextEdit;
class QImage;
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
