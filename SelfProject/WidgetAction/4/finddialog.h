#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QCheckBox;
class QLineEdit;
QT_END_NAMESPACE

class FindDialog : public QDialog {
  Q_OBJECT

 public:
  FindDialog(QWidget *parent = 0);
  ~FindDialog();

  /// must be public
 signals:
  void findNext(const QString &str, Qt::CaseSensitivity cs);
  void findPrevious(const QString &str, Qt::CaseSensitivity cs);

 private slots:
  void enabledFindButton(const QString &text);
  void findClicked();

 private:
  QLabel *label;
  QCheckBox *caseCheckBox;
  QCheckBox *backwardCheckBox;
  QLineEdit *lineEdit;
  QPushButton *findButton;
  QPushButton *closeButton;
};

#endif  // FINDDIALOG_H
