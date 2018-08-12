////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// COPYRIGHT (c) 2018, 金小海
/// All rights reserved.
///
/// @file    This file is part of the 1 project.
/// @version 1.0
/// @author  jinxiaohai <xiaohaijin@outlook.com>
/// @date    2018 07 09    19:41:18
/// @brief
///
/// 修订说明:最初版本
////////////////////////////////////////////////////////////////////////
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QLabel *label =
      new QLabel("<h1><b>Hello </b> <font color=red>Qt</font></h1>");
  label->show();

  return a.exec();
}
