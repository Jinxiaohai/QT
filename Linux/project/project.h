#ifndef PROJECT_H
#define PROJECT_H

#include <QtCore/qglobal.h>
#include <QString>

class Project {
 public:
  Project();

  void createDir();
  void createLicence();
  void createREADME();
  void createRootCMakeLists();
  void createSrcCMakeLists();

  void run();

 private:
  QString currentPath;
};

#endif  // PROJECT_H
