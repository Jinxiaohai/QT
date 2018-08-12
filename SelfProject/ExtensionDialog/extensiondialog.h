#ifndef EXTENSIONDIALOG_H
#define EXTENSIONDIALOG_H

#include <QDialog>

class ExtensionDialog : public QDialog {
  Q_OBJECT

 public:
  ExtensionDialog(QWidget *parent = 0);
  ~ExtensionDialog();

 private slots:
  void showDetailInfo();

 private:
  void createBaseInfo();
  void createDetailInfo();
  QWidget *baseWidget;
  QWidget *detailWidget;
};

#endif  // EXTENSIONDIALOG_H
