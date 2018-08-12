#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QProgressBar;
class QComboBox;
class QPushButton;
class QGridLayout;
QT_END_NAMESPACE

class ProgressDialog : public QDialog {
  Q_OBJECT

 public:
  ProgressDialog(QWidget *parent = 0);
  ~ProgressDialog();

 private slots:
  void startProgress();

 private:
  QLabel *FileNum;
  QLineEdit *FileNumLineEdit;
  QLabel *ProgressType;
  QComboBox *comboBox;
  QProgressBar *progressBar;
  QPushButton *startBtn;
  QGridLayout *mainLayout;
};

#endif  // PROGRESSDIALOG_H
