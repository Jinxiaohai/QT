#ifndef BASEINFO_H
#define BASEINFO_H

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
class BaseInfo : public QWidget {
  Q_OBJECT
 public:
  explicit BaseInfo(QWidget *parent = 0);

 signals:

 public slots:
 private:
  //左侧
  QLabel *UserNameLabel;
  QLabel *NameLabel;
  QLabel *SexLabel;
  QLabel *DepartmentLabel;
  QLabel *AgeLabel;
  QLabel *OtherLabel;
  QLineEdit *UserNameLineEdit;
  QLineEdit *NameLineEdit;
  QComboBox *SexComboBox;
  QTextEdit *DepartmentTextEdit;
  QLineEdit *AgeLineEdit;
  QGridLayout *LeftLayout;
  //右侧
  QLabel *HeadLabel;  //右上角部分
  QLabel *HeadIconLabel;
  QPushButton *UpdateHeadBtn;
  QHBoxLayout *TopRightLayout;
  QLabel *IntroductionLabel;
  QTextEdit *IntroductionTextEdit;
  QVBoxLayout *RightLayout;
};

#endif  // BASEINFO_H
