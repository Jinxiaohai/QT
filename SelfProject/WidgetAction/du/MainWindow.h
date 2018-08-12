////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// COPYRIGHT (c) 2018, 金小海
/// All rights reserved.
///
/// @file    This file is part of the du project.
/// @version 1.0
/// @author  jinxiaohai <xiaohaijin@outlook.com>
/// @date    2018 05 16    19:30:34
/// @brief
///
/// 修订说明:最初版本
////////////////////////////////////////////////////////////////////////
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QChartView>
#include <QPieSeries>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QGridLayout;
class QPushButton;
class QHBoxLayout;
class QDir;
class QProgressDialog;
QT_END_NAMESPACE

using namespace QtCharts;

class MainWindow : public QWidget {
  Q_OBJECT
 public:
  typedef QPair<QString, unsigned long int> EachUser;

  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() {}

  /// ADTs
  QStringList getUsersName() const;
  void getSize(QString path);

 signals:
  void getPathError();
  void getUsersNameError();

 public slots:
  void start();
  void doPathError();
  void doUsersError();
  void sendError();

 private:
  QLabel *pathLabel;
  QLineEdit *pathLineEdit;

  QLabel *userNameLabel;
  QLineEdit *userNameLineEdit;

  QWidget *centralWidget;
  QChartView *chartView;

  QPushButton *startButton;
  QPushButton *closeButton;

  QString errorMessage;

  QGridLayout *mainLayout;

  QStringList allUsers;
  QVector<EachUser> allInformation;
};

#endif  // MAINWINDOW_H
