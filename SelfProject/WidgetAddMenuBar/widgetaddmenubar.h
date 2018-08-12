#ifndef WIDGETADDMENUBAR_H
#define WIDGETADDMENUBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QMenuBar;
QT_END_NAMESPACE

class WidgetAddMenuBar : public QWidget {
  Q_OBJECT

 public:
  WidgetAddMenuBar(QWidget *parent = 0);
  ~WidgetAddMenuBar();

 private:
  QMenuBar *menuBar;
};

#endif  // WIDGETADDMENUBAR_H
