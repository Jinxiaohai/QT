#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QDateTimeEdit;
class QSpinBox;
class QDoubleSpinBox;
class QGroupBox;
class QLabel;
QT_END_NAMESPACE

///
///
///
class Window : public QWidget {
  Q_OBJECT
 public:
  explicit Window(QWidget *parent = nullptr);
  void setMyStyleSheet();

 public
slots:
  void changePrecision(int decimals);
  void setFormatString(const QString &formatString);

 private:
  void createSpinBoxes();
  void createDateTimeEdits();
  void createDoubleSpinBoxes();

  QDateTimeEdit *meetingEdit;

  QDoubleSpinBox *doubleSpinBox;
  QDoubleSpinBox *priceSpinBox;
  QDoubleSpinBox *scaleSpinBox;

  QGroupBox *spinBoxesGroup;
  QGroupBox *editsGroup;
  QGroupBox *doubleSpinBoxesGroup;

  QLabel *meetingLabel;
  QSpinBox *groupSeparatorSpinBox;
  QDoubleSpinBox *groupSeparatorSpinBox_d;
};

#endif  // WINDOW_H
