#include <QString>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QThread>
#include <QEventLoop>
#include <QCoreApplication>
#include <QAbstractEventDispatcher>

#include <QMessageBox>
#include <QPushButton>
#include <QNetworkInterface>
#include <QUuid>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QSharedMemory>
#include "base.h"

QString getTime(){
    //js 返回unix毫秒数
    QDateTime now = QDateTime::currentDateTime();
    QDateTime _1970 = QDateTime(QDate(1970,1,1),QTime(8,0));
    qint64 base = _1970.msecsTo(now);
    return QString::number(base);
}

QString getUnixTime(int expires_s){
    //返回unix秒数，参数为增加的秒数，未来的expires_s秒数
    QDateTime time;
    if(expires_s == 0)
        time = QDateTime::currentDateTime();
    else{
        time = QDateTime::currentDateTime().addSecs(expires_s);
    }
    QDateTime _1970 = QDateTime(QDate(1970,1,1),QTime(0,0,0));
    qint64 base = _1970.msecsTo(time)/1000;
    return QString::number(base);
}

QByteArray gAccessResult(QNetworkAccessManager *manager, const QString &url, const Header &refer, const QByteArray &array){
    QNetworkReply * reply;
    if(array.isEmpty()){
        reply = gAccessReply(manager,url,refer);
        int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if(status == 302 || status == 301){
            QString url = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
            reply->deleteLater();
            return gAccessResult(manager,url,refer);
        }
    }else{
        reply = gAccessReply(manager,url,refer,array);
    }
    QByteArray result = reply->readAll();
    reply->deleteLater();
    return result;
}

QNetworkReply * gAccessReply(QNetworkAccessManager *manager, const QString & url, const Header &refer, const QByteArray & array){
    QNetworkRequest logrequest;
    QNetworkReply * reply;
    QEventLoop loop;
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));
    logrequest.setUrl(QUrl(url));
    if(array.isEmpty())
        logrequest.setRawHeader("Content-Type","text/html;charset=UTF-8");
    else
        logrequest.setRawHeader("Content-Type","application/x-www-form-urlencoded;charset=UTF-8");//必须为这种content
    logrequest.setRawHeader("Accept","text/html,application/xhtml+xml,*/*");
    logrequest.setRawHeader("Connection","keep-alive");
    if(!refer.isEmpty()){
        for(Header::const_iterator it = refer.begin(); it != refer.end(); ++it){
            logrequest.setRawHeader(it.key().toUtf8(),it.value().toUtf8());
        }
    }
    logrequest.setRawHeader("User-Agent",HTTP_USER_AGENT);
    if(array.isEmpty())
        reply = manager->get(logrequest);
    else
        reply = manager->post(logrequest,array);
    loop.exec();
    QObject::disconnect(manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));
    return reply;
}

QString getMACAdress()  {
    QNetworkInterface thisNet;      //所要使用的网卡
    QList<QNetworkInterface> NetList = QNetworkInterface::allInterfaces();//获取所有网卡信息
    int NetCount = NetList.count();         //统计网卡个数
    for(int Neti = 0;Neti < NetCount; Neti++){   //遍历所有网卡
        thisNet = NetList[Neti];    //将该网卡置为当前网卡
        if(thisNet.isValid() && thisNet.flags().testFlag(QNetworkInterface::IsUp) && thisNet.flags().testFlag(QNetworkInterface::IsRunning)){    //判断该网卡是否是合法
            break;
        }
    }
    return thisNet.hardwareAddress();   //获取该网卡的MAC
}

int showMessagebox(const QString &title, const QString &text, int icon){
    static QMessageBox * box = nullptr;
    if(!box){
        box = new QMessageBox(0);
        QPushButton * ok = box->addButton(QMessageBox::Ok);
        ok->setText("确定");
        QPushButton * cancel = box->addButton(QMessageBox::Cancel);
        cancel->setText("取消");
    }
    box->setWindowTitle(title);
    box->setIcon(QMessageBox::Icon(icon));
    box->setText(text);

    return box->exec();
}

void showMessageWithUnmode(const QString &title, const QString &text, int icon,QWidget *parent){
    QMessageBox * box = new QMessageBox(parent);
    box->setModal(false);
    box->setAttribute(Qt::WA_DeleteOnClose);//关闭对话框自动析构
    box->setWindowTitle(title);
    box->setIcon(QMessageBox::Icon(icon));
    box->setText(text);
    QPushButton * ok = box->addButton(QMessageBox::Ok);
    ok->setText("关闭");
    QObject::connect(ok,&QPushButton::clicked,[box](){box->close();});
    box->activateWindow();
    box->showNormal();
    box->raise();
}

void g_mySleep(float sec){
    QTime t;
    t.start();
    sec *= 1000;
    QAbstractEventDispatcher * dispatcher = QThread::currentThread()->eventDispatcher();
    if(dispatcher == NULL){
        tkgDebug("休眠无效");
    }
    /*关于误差：很小，因t.elapsed()是一直在走的，产生的时差是当无限接近于sec，然后休眠100ms，此时将产生±100ms
     *关于休眠：1.是为了让出cpu，使线程可以执行其他线程。2：分配事件派发的时间。
    */
    while(t.elapsed() < sec){
        dispatcher->processEvents(QEventLoop::AllEvents);
        QThread::currentThread()->usleep(100);
    }
}

QString getAbsoluteFileName(const QString &path,const QString fileName){
    QString myPath = createDirWithName(path);
    if(myPath.isEmpty())
        return "";
#ifdef Q_OS_WIN32
    return myPath + "\\" +fileName;
#else
    return myPath + "/" + fileName;
#endif
}

QString createDirWithName(const QString &dir_name){
    //QDir默认构造为当前路径，当创建是以当前路径为开始创建的
    //macos的运行方式和windows是有区别的。
#ifdef Q_OS_WIN32
    QDir dir = QDir::currentPath() + "\\" +dir_name;
    QStringList list = dir.absolutePath().split("\\");
    QString mid = "\\";
#else
    QDir dir = QDir::currentPath() + "/" +dir_name;
    QStringList list = dir.absolutePath().split("/");
    QString mid = "/";
#endif
    if(dir.exists()){
        return dir.absolutePath();
    }
    QString path;
    for(QStringList::const_iterator it = list.begin(); it != list.end(); ++it){
        path += *it;
        path += mid;
        if(!dir.exists(path))
            if(!dir.mkdir(path)){
                showMessagebox("错误","创建文件夹失败"+dir.absolutePath(),QMessageBox::Critical);
                return "";
            }
    }
    return dir.absolutePath();
}

bool downFile(const QString &url,const QString &absolutePathAndName){
    QFile file(absolutePathAndName);
    if(file.exists()){
        return true;
    } else {
        if(!file.open(QIODevice::WriteOnly)){
            return false;
        }else{
            QNetworkAccessManager manager;
            QByteArray result = gAccessResult(&manager,url);
            file.write(result);
            file.close();
            return true;
        }
    }
}

QString hmacSha1(QByteArray key, QByteArray baseString){
    int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
    if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }

    QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
    QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "quot;

    for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
        outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
    }
    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(baseString);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
    return hashed.toBase64();
}

QString getHashMd5(const QString &filePath){
    QString md5;
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray array = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5);
        md5 = QString(array.toHex());
    }
    file.close();
    return md5;
}
bool assumeSingleInstance(const char* program){
    static QSharedMemory shm(program);
    if(shm.create(2) == false){
        return true;
    }
    return false;
}
