#ifndef QLCDDIALOG_H
#define QLCDDIALOG_H

#include <QDialog>

class QLCDDialog : public QDialog
{
  Q_OBJECT

public:
  QLCDDialog(QWidget *parent = 0);
  ~QLCDDialog();
};

#endif // QLCDDIALOG_H
