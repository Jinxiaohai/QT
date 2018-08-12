#ifndef LINE_H
#define LINE_H

#include <QMainWindow>

namespace Ui {
class Line;
}

class Line : public QMainWindow {
  Q_OBJECT

 public:
  explicit Line(QWidget *parent = 0);
  ~Line();

 protected:
  void changeEvent(QEvent *e);

 private:
  Ui::Line *ui;

  void createChart();
};

#endif  // LINE_H
