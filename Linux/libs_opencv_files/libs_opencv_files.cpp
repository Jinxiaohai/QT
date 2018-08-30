#include <iostream>

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfoList>

#include "libs_opencv_files.h"

libs_opencv_files::libs_opencv_files(const QString &pathName) {
  this->pathName = pathName;
}

void libs_opencv_files::GetLibs() const {
  QDir opencvLibDir(pathName);
  QFileInfoList files =
      opencvLibDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);

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
