#ifndef LIBS_ROOT_FILES_H
#define LIBS_ROOT_FILES_H

#include <QString>

class libs_root_files {
 public:
  libs_root_files(const QString &pathName = "/opt/root/install/lib");
  virtual ~libs_root_files() {}
  virtual void GetLibs() const;

 private:
  QString pathName;
};

#endif  // LIBS_ROOT_FILES_H
