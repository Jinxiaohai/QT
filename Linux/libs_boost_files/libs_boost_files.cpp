#include <iostream>

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfoList>

#include "libs_boost_files.h"

libs_boost_files::libs_boost_files(const QString &pathName) {
  this->pathName = pathName;
}

void libs_boost_files::GetLibs() const {
  QDir boostLibDir(pathName);
  QFileInfoList files =
      boostLibDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);

  QStringList soFiles;
  foreach (QFileInfo eachFile, files) {
    if (eachFile.fileName().endsWith("so") &&
        eachFile.fileName().startsWith("lib")) {
      soFiles.append(eachFile.baseName().replace(0, 3, "-l"));
    }
  }

  QString result = "-L" + pathName;
  foreach (QString eachFile, soFiles) { result.append(" " + eachFile); }

  std::cout << result.toStdString() << std::endl;
}
