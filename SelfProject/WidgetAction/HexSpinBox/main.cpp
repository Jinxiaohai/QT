////////////////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// COPYRIGHT (c) 2018, 金小海
/// All rights reserved.
///
/// @file    This file is part of the HexSpinBox project.
/// @version 1.0
/// @author  jinxiaohai <xiaohaijin@outlook.com>
/// @date    2018 07 12    12:03:01
/// @brief
///
/// 修订说明:最初版本
////////////////////////////////////////////////////////////////////////
#include <QApplication>
#include "hexspinbox.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  HexSpinBox hexSpinBox;
  hexSpinBox.show();

  return a.exec();
}
