#ifndef SPLITTERDIALOG_H
#define SPLITTERDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QSplitter;
QT_END_NAMESPACE

class SplitterDialog : public QDialog {
  Q_OBJECT

 public:
  SplitterDialog(QWidget *parent = 0);
  ~SplitterDialog();

private:
  QSplitter *splitter;
};

#endif  // SPLITTERDIALOG_H
