#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if QT_VERSION >= 0x050000
#include <QMainWindow>
#else
#include <QMainWindow>
#endif

#include <QFileSystemWatcher>

namespace Ui {
class MainWindow;
}
class QFile;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 protected:
  void changeEvent(QEvent *e);

 private
slots:
  void showMessage(const QString &path);

 private:
  Ui::MainWindow *ui;
  QFileSystemWatcher myWatcher;
  QFile *qssFile;
};

#endif  // MAINWINDOW_H
