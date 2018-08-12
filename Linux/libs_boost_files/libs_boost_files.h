#ifndef LIBS_BOOST_FILES_H
#define LIBS_BOOST_FILES_H

#include <QString>

class libs_boost_files {
 public:
  libs_boost_files(const QString &pathName = "/opt/boost/install/lib");
  virtual ~libs_boost_files() {}
  virtual void GetLibs() const;

 private:
  QString pathName;
};

#endif  // LIBS_BOOST_FILES_H
