////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// COPYRIGHT (c) 2017, 金小海
/// All rights reserved.
/// 
/// @file    window.h
/// @version 1.0
/// @author  jinxiaohai <jinxiaohaijin@outlook.com>
/// @date    Wed Apr 25 15:53:44 2018
/// 
/// @brief   基本按钮和组合框的练习。
/// 
/// 修订说明:最初版本
////////////////////////////////////////////////////////////////////////
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_MOC_NAMESPACE

class Window : public QWidget {
  Q_OBJECT
 public:
  explicit Window(QWidget *parent = nullptr);

 signals:

 public slots:

 private:
  /// 创建四个组合框
  QGroupBox *createFirstExclusiveGroup();
  QGroupBox *createSecondExclusiveGroup();
  QGroupBox *createNonExclusiveGroup();
  QGroupBox *createPushButtonGroup();
};

#endif  // WINDOW_H
