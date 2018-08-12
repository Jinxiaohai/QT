#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QSpinBox;
class QStackedWidget;
QT_END_NAMESPACE
class SlidersGroup;

class Window : public QWidget {
  Q_OBJECT
 public:
  explicit Window(QWidget *parent = nullptr);

 signals:

 public slots:

 private:
  void createControls(const QString &title);

  SlidersGroup *horizontalSliders;
  SlidersGroup *verticalSliders;
  QStackedWidget *stackedWidget;

  QGroupBox *controlsGroup;
  QLabel *minimumLabel;
  QLabel *maximumLabel;
  QLabel *valueLabel;
  QCheckBox *invertedAppearance;
  QCheckBox *invertedKeyBindings;
  QSpinBox *minimumSpinBox;
  QSpinBox *maximumSpinBox;
  QSpinBox *valueSpinBox;
  QComboBox *orientationCombo;
};

#endif  // WINDOW_H
