#ifndef LAYOUT_H
#define LAYOUT_H

#include <QWidget>

namespace Ui {
class Layout;
}

class Layout : public QWidget {
  Q_OBJECT

 public:
  explicit Layout(QWidget *parent = 0);
  ~Layout();

 protected:
  void changeEvent(QEvent *e);

 private:
  Ui::Layout *ui;
};

#endif  // LAYOUT_H
