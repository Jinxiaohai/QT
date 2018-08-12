#include <QCoreApplication>
#include "base.h"
#include "log.h"
#include "base64.h"
#include "httpdownload.h"
#include "md5.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(assumeSingleInstance("myapp.lock")){
        showMessagebox(QObject::tr("错误"),QObject::tr("程序已运行，查看右下角图标"),QMessageBox::Critical);
        exit(0);
    }
    return a.exec();
}
