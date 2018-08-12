#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;
QT_END_NAMESPACE

class FindDialog : public QDialog {
  Q_OBJECT

 public:
  FindDialog(QWidget *parent = 0);
  ~FindDialog();

 private:
  QLabel *namedLabel;
  QLabel *lookInLabel;
  QLineEdit *namedLineEdit;
  QLineEdit *lookInLineEdit;

  QCheckBox *subfoldersCheckBox;

  QTableWidget *tableWidget;

  QLabel *messageLabel;

  QPushButton *findButton;
  QPushButton *stopButton;
  QPushButton *closeButton;
  QPushButton *helpButton;
};

#endif  // FINDDIALOG_H
