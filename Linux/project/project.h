#ifndef PROJECT_H
#define PROJECT_H

#include <QtCore/qglobal.h>
#include <QString>
#include <QObject>

class Project : public QObject {
  Q_OBJECT
  
 public:
  Project(QObject *parent = 0);

  void createDir();
  void createLicence();
  void createREADME();
  void createResources();
  void createRootCMakeLists();
  void createSrcCMakeLists();
  void setPropertity();

  void moveFile();
  void addFile();

  void run();

 private:
  QString getFormatFiles(const QString &dirName, const QString &format);

  QString currentPath;
  bool isQt;
};

#endif  // PROJECT_H
