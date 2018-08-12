#include <iostream>

#include <QDir>
#include <QStringList>

#include "INCDIR.h"

INCDIR::INCDIR(QString StRoot) { this->StRoot = StRoot; }

void INCDIR::getIncludeDir() {
  QDir dir(StRoot);
  result = dir.entryList(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
}

void INCDIR::print() {
  this->getIncludeDir();

  for (int i = 0; i != result.size(); ++i) {
    std::cout << (this->StRoot + QDir::separator() + result.at(i)).toStdString()
              << "  ";
  }
}
