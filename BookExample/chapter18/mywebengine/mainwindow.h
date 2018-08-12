#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if QT_VERSION >= 0x050000
#include <QMainWindow>
#else
#include <QMainWindow>
#endif

namespace Ui {
class MainWindow;
}
class QWebEngineView;
class QLineEdit;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 protected:
  void changeEvent(QEvent *e);

 protected
slots:
  void changeLocation();
  void setProgress(int p);
  void adjustTitle();
  void finishLoading(bool);

 private:
  Ui::MainWindow *ui;
  QWebEngineView *view;

  QLineEdit *locationEdit;
  int progress;
};

#endif  // MAINWINDOW_H
