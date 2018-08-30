#ifndef LIBS_OPENCV_FILES_H
#define LIBS_OPENCV_FILES_H

#include <QString>

class libs_opencv_files {
 public:
  libs_opencv_files(const QString &pathName = "/opt/opencv/install/lib64");
  virtual ~libs_opencv_files() {}
  virtual void GetLibs() const;

 private:
  QString pathName;
};

#endif  // LIBS_OPENCV_FILES_H
