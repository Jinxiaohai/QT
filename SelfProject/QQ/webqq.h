/****************************************************************************
**
** Copyright (C) 2013 Jeffrey Lee.
** All rights reserved.
** Contact: vipjeffreylee@gmail.com
** Please keep the author contact information.
** 2013-10-10
**
****************************************************************************/
#ifndef WEBQQ_H
#define WEBQQ_H
#include <QList>
#include <QMutex>
#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include "qqfriend.h"
#include "qqgroup.h"
#include "qqmsg.h"
#include "webqqnet.h"
// class WebQQNet;
class LoginDlg;
class MainWindow;
enum class QQstatus { online, offline };

namespace WebQQ {
class Msg : public QObject {
  Q_OBJECT
 public:
  explicit Msg(QObject* parent = 0);

 signals:

 public slots:
};

extern QQstatus status;
extern WebQQNet* webQQNet;
extern LoginDlg* loginDlg;
extern MainWindow* mainWindow;
extern void login();
extern void loginFinished(bool ok);
extern QString qqnum;
extern QHash<QString, QQgroup*> qqGroups;
extern QHash<QString, QQfriend*> qqFriends;
extern QList<QQmsg*> qqmsgs;
extern QStandardItemModel* qqGroupListModel;
extern QStandardItemModel* qqFriendListModel;
extern bool isclose;
extern QMutex mutex;
}  // namespace WebQQ
#endif  // WEBQQ_H
