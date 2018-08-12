////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// COPYRIGHT (c) 2018, 金小海
/// All rights reserved.
///
/// @file    This file is part of the 2 project.
/// @version 1.0
/// @author  jinxiaohai <xiaohaijin@outlook.com>
/// @date    2018 07 09    19:48:03
/// @brief
///
/// 修订说明:最初版本
////////////////////////////////////////////////////////////////////////
#include <QApplication>
#include <QPushButton>
#include <QtGlobal>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QPushButton *pushButton = new QPushButton("Click Me");
  QObject::connect(pushButton, SIGNAL(clicked()), &a, SLOT(quit()));
  pushButton->resize(400, 200);
  pushButton->show();

  return a.exec();
}
