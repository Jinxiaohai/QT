#include <QDebug>
#include <QStandardPaths>
#include <QString>

#include "username.h"

int main(int argc, char *argv[]) {
  UserName usesName;
  qDebug() << usesName.getUsersName();
}
