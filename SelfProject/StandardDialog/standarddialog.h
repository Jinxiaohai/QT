#ifndef STANDARDDIALOG_H
#define STANDARDDIALOG_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QPushButton;
class QErrorMessage;
class QWizardPage;
QT_END_MOC_NAMESPACE

class StandardDialog : public QMainWindow {
  Q_OBJECT
 public:
  explicit StandardDialog(QWidget *parent = nullptr);

 signals:

 public slots:
  void showColorDialog();
  void showFileDialog();
  void showFontDialog();
  void showInputDialog();
  void showMessageDialog();
  void showProgressDialog();
  void showErrorMessageDialog();
  void showWizardDialog();

 private:
  QPushButton *colorPushButton;
  QPushButton *filePushButton;
  QPushButton *fontPushButton;
  QPushButton *inputPushButton;
  QPushButton *messagePushButton;
  QPushButton *progressPushButton;
  QPushButton *errorMessagePushButton;
  QPushButton *wizardPagePushButton;
  QErrorMessage *errordlg;

  QWidget *widget;

  QWizardPage *createPage1();
  QWizardPage *createPage2();
  QWizardPage *createPage3();
};

#endif  // STANDARDDIALOG_H
