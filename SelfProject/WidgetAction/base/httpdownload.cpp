#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QEventLoop>

#include "httpdownload.h"

HttpDownload::HttpDownload(QWidget *widget, QObject *parent) :
    QObject(parent),m_manager(new QNetworkAccessManager(0)),m_loop(new QEventLoop){
    m_widget = widget;
}

void HttpDownload::replyNewDate(){
    if(m_file){
        m_file->write(m_reply->readAll());
        m_file->flush();
    }
}

void HttpDownload::replyFinished(){
    // 能通过reply读取请求的所有数据大小和吗？貌似很难，这种流式数据
    m_reply->deleteLater();
    m_file->close();
    m_file->deleteLater();
    emit finished();
}

void HttpDownload::replyError(){
    m_down_size = 0;
    emit finished();
}

void HttpDownload::replyProgress(qint64 recv,qint64 total){
    m_down_size = total;//当数据大时，这会被重复设置
}

int HttpDownload::downloadFile(const QString &url, const QString &file, const QString &dir){
    m_reply = m_manager->get(QNetworkRequest(QUrl(url+file)));
    if(dir.isEmpty()){
        m_file = new QFile(file);
        return 0;
    }else{
        QDir directory(dir);
        if(!directory.exists()){
            directory.mkpath(dir);
        }
        if(dir.endsWith("/"))
            m_file = new QFile(dir+file);
        else
            m_file = new QFile(dir+"/"+file);
    }
    if(!m_file->open(QIODevice::WriteOnly)){
        QMessageBox::warning(0,"错误","文件打开失败",QMessageBox::Ok);
        return 0;
    }
    connect(m_reply,SIGNAL(readyRead()),this,SLOT(replyNewDate()));

    connect(m_reply,SIGNAL(finished()),this,SLOT(replyFinished()));

    connect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(replyError()));

    connect(m_reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(replyProgress(qint64,qint64)));
    connect(this,SIGNAL(finished()),m_loop,SLOT(quit()));
    m_loop->exec();
    return m_down_size;
}

