/****************************************************************************
**  @copyright  TinKinG
**  @contract   lsnbing@126.com
**
**  @brief  http下载类
**  @file   httpdownload.h
**  @author TinKinG
**  @date   2017-02-15
**
**
*****************************************************************************/
#ifndef HTTPDOWNLOAD_H
#define HTTPDOWNLOAD_H
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QFile;
class QEventLoop;
class QWidget;
class HttpDownload : public QObject
{
    Q_OBJECT

    QNetworkAccessManager *m_manager;//网络参数
    QNetworkReply * m_reply;

    QString m_fileName;
    QString m_dir;

    QEventLoop *m_loop;

    QFile * m_file;

    qint64 m_recv_size;
    qint64 m_total_size;

    QWidget * m_widget;
    int m_down_size;
public:
    explicit HttpDownload(QWidget * widget,QObject *parent = 0);
    // 返回下载文件大小，返回0-下载错误
    int downloadFile(const QString &url,const QString &file,const QString &dir="");
signals:
    void finished();
private slots:
    void replyNewDate();
    void replyFinished();
    void replyProgress(qint64 recv,qint64 total);
    void replyError();
};

#endif // HTTPDOWNLOAD_H
