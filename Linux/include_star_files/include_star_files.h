#ifndef INCDIR_H
#define INCDIR_H

#include <QStringList>

class INCDIR {
 public:
  INCDIR(QString StRoot = "/home/xiaohai/Github/analysisNote/code/StRoot");

  void print();

 private:
  void getIncludeDir();

  QString StRoot;
  QStringList result;
};

#endif  // INCDIR_H
