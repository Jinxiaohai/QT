#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if QT_VERSION >= 0x050000
#include <QMainWindow>
#else
#include <QMainWindow>
#endif

#include <QUrl>

namespace Ui {
class MainWindow;
}
class QFile;
class QNetworkReply;
class QNetworkAccessManager;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void startRequest(QUrl url);

 protected:
  void changeEvent(QEvent *e);

 private
slots:
  void httpFineshed();
  void httpReadyRead();
  void updateDataReadProgress(qint64, qint64);

  void on_pushButton_clicked();

 private:
  Ui::MainWindow *ui;
  QNetworkAccessManager *manager;
  QNetworkReply *reply;
  QUrl url;
  QFile *file;
};

#endif  // MAINWINDOW_H
