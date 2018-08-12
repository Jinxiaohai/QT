#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QComboBox;
class QTextEdit;
class QGridLayout;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
QT_END_NAMESPACE

class Dialog : public QDialog {
  Q_OBJECT

 public:
  Dialog(QWidget *parent = 0);
  ~Dialog();

 private:
  /// Left widget
  QLabel *UserNameLabel;
  QLineEdit *UserNameLineEdit;

  QLabel *NameLabel;
  QLineEdit *NameLineEdit;

  QLabel *SexLabel;
  QComboBox *SexComboBox;

  QLabel *DepartmentLabel;
  QTextEdit *DepartmentTextEdit;

  QLabel *AgeLabel;
  QLineEdit *AgeLineEdit;

  QLabel *OtherLabel;
  QGridLayout *LeftLayout;

  /// Right widget
  QLabel *HeadLabel;
  QLabel *HeadIconLabel;
  QPushButton *UpdateHeadBtn;

  QHBoxLayout *TopRightLayout;

  QLabel *IntroductionLabel;
  QTextEdit *IntroductionTextEdit;

  QVBoxLayout *RightLayout;

  /// Bottom widget
  QPushButton *OkBtn;
  QPushButton *CancelBtn;

  QHBoxLayout *ButtomLayout;
};

#endif  // DIALOG_H
