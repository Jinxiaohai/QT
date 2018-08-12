#ifndef USERNAME_H
#define USERNAME_H

#include <QStringList>

class UserName {
 public:
  UserName();
  QStringList getUsersName();

 private:
  QStringList usersName;
};

#endif  // USERNAME_H
