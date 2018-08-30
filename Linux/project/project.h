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
  void createResources();
  void createRootCMakeLists();
  void createSrcCMakeLists();
  void setPropertity();

  void run();

 private:
  QString currentPath;
  bool isQt;
};

#endif  // PROJECT_H
