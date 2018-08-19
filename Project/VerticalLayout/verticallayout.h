#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

#include <QDialog>

namespace Ui {
class VerticalLayout;
}

class VerticalLayout : public QDialog {
  Q_OBJECT

 public:
  explicit VerticalLayout(QWidget *parent = 0);
  ~VerticalLayout();

 protected:
  void changeEvent(QEvent *e);

 private:
  Ui::VerticalLayout *ui;
};

#endif  // VERTICALLAYOUT_H
