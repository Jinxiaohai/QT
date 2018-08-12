#ifndef PRINTER_H
#define PRINTER_H

#include <QMainWindow>

namespace Ui {
class Printer;
}

QT_BEGIN_NAMESPACE
class QPrinter;
QT_END_NAMESPACE

class Printer : public QMainWindow {
  Q_OBJECT

 public:
  explicit Printer(QWidget *parent = 0);
  ~Printer();

 protected:
  void changeEvent(QEvent *e);

 private slots:
  void doPrint();
  void doPrintPreview();
  void printPreview(QPrinter *printer);
  void createPdf();

 private:
  Ui::Printer *ui;
};

#endif  // PRINTER_H
