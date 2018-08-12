/****************************************************************************
**  @copyright  TinKinG
**  @contract   lsnbing@126.com
**
**  @brief  一些常用函数
**  @file   base.h
**  @author TinKinG
**  @date   2016-06-07
**
**  需开启C++11支持
**  QMAKE_CFLAGS +=  -std=c99
**  QMAKE_CXXFLAGS += -std=c++11
**  需加入network模块
**
*****************************************************************************/
#ifndef BASE_H
#define BASE_H

#include <QMap>
#include <QList>
#include <QString>
#include <QVector>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

/*
 * 常规常量
*/

#ifndef TKG_ON
#define TKG_ON  1
#endif

#ifndef TKG_OFF
#define TKG_OFF 0
#endif

#define TKG_ERROR               "ERR"
#define TKG_WARN                "WAR"
#define TKG_INFO                "INF"

#define STYLE_GREEN             "<span style='color:green'>%1</span>"
#define STYLE_RED               "<span style='color:red'>%1</span>"

#define HTTP_KEY_REFERER             "Referer"
#define HTTP_KEY_X_REQUESTED_WITH    "X-Requested-With"
#define HTTP_VALUE_REQUEST_XML       "XMLHttpRequest"
#define HTTP_VALUE_REQUEST_SWF       "ShockwaveFlash/22.0.0.192"
#define HTTP_USER_AGENT              "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2840.71 Safari/537.36"

/*
 * Log输出
*/

#ifndef G_DEBUG
#define G_DEBUG QObject::tr(__FILE__) << QObject::tr("%1").arg(__LINE__)
#endif

#ifdef MODEL_DEBUG_CMP
#   ifndef tkgDebug
#   define tkgDebug(ss)    (qDebug() << G_DEBUG << ss)
#   endif
#else
#   ifndef tkgDebug
#   define tkgDebug(ss) (0)                // 展开后都是局部变量，同一函数多次使用没问题
#   endif
#endif

#define Q_CS(s) ((s).toStdString().c_str())// QString转标准字符串


/*
 * QString多格式输出<<
*/

class QByteArray;
class QNetworkAccessManager;
class QNetworkReply;

typedef QMap<QString,QString> Header;

// 显示模态对话框（可选择使用原生的对话框QMessageBox::information...）
int showMessagebox(const QString &title, const QString &text, int icon);
// 显示非模态对话框
void showMessageWithUnmode(const QString &title, const QString &text, int icon, QWidget *parent = 0);
// 访问重定向的最终结果
QByteArray gAccessResult(QNetworkAccessManager *manager, const QString & url,const Header &refer=Header(), const QByteArray & array=0);
// 返回网址的直接reply（非重定向）
QNetworkReply * gAccessReply(QNetworkAccessManager *manager, const QString & url,const Header &refer = Header(),const QByteArray & array=0);
// 返回MAC地址
QString getMACAdress();
// 获取1970.1.1 08:00 至今的毫秒数
QString getTime();
// 获取Unix的秒数
QString getUnixTime(int expires_s);
// KEY-MD5码
QString hmacSha1(QByteArray key, QByteArray baseString);
// 获取文件MD5值（md5sum相同计算值）
QString getHashMd5(const QString &filePath);
// 单实例进程
bool assumeSingleInstance(const char* program);
// GUI非阻塞休眠
void g_mySleep(float sec);
// 在当前工作路径创建目录
QString createDirWithName(const QString &dir_name);
// 得到一个工作路径下的文件名的绝对路径（如果没有则创建）
QString getAbsoluteFileName(const QString &path,const QString fileName);
// 保存一个完成的路径名（需要完整的URL,仅适合小文件如网页等）
bool downFile(const QString &url, const QString &absolutePathAndName);

// 重载QString的<<操作符
inline QString operator<<(const QString &s,const QString &a){ QString tmp = s; return tmp.append(" ").append(a);}
inline QString operator<<(const QString &s,const char *a){ QString tmp = s;return operator<<(tmp,QString::fromUtf8(a)); }
inline QString operator<<(const QString &s,bool t) { QString tmp = s;return tmp.append(" ").append(t ? "true" : "false"); }
inline QString operator<<(const QString &s,char t) { QString tmp = s; return tmp.append(" ").append(t);}
inline QString operator<<(const QString &s,const QChar t) {QString tmp = s; return operator<<(tmp,t.toLatin1()); }
inline QString operator<<(const QString &s,signed short t) { QString tmp = s;return tmp.append(" ").append(QString::number(t));}
inline QString operator<<(const QString &s,unsigned short t) {QString tmp = s; return tmp.append(" ").append(QString::number(t));}
inline QString operator<<(const QString &s,signed int t) { QString tmp = s;return tmp.append(" ").append(QString::number(t)); }
inline QString operator<<(const QString &s,unsigned int t) {QString tmp = s; return tmp.append(" ").append(QString::number(t)); }
inline QString operator<<(const QString &s,signed long t) { QString tmp = s;return tmp.append(" ").append((QString::number(t)));  }
inline QString operator<<(const QString &s,unsigned long t) {QString tmp = s; return tmp.append(" ").append(QString::number(t)); }
inline QString operator<<(const QString &s,qint64 t) { QString tmp = s;return tmp.append(" ").append(QString::number(t)); }
inline QString operator<<(const QString &s,quint64 t) { QString tmp = s;return tmp.append(" ").append(QString::number(t)); }
inline QString operator<<(const QString &s,float t) { QString tmp = s;return tmp.append(" ").append(QString::number(t)); }
inline QString operator<<(const QString &s,double t) { QString tmp = s;return tmp.append(" ").append(QString::number(t)); }
inline QString operator<<(const QString &s,const QByteArray &t) { QString tmp = s;return tmp.append(" ").append(t); }
inline QString operator<<(const QString &s,const void * t) {QString tmp = s; return tmp.append(" ").append(QString::number(reinterpret_cast<long>(t))); }
template <class T>
inline QString operator<<(const QString &s, const QList<T> &list){
    QString tmp = s;
    tmp.append(" (");
    for (typename QList<T>::size_type i = 0; i < list.count(); ++i) {
        if(i) tmp.append(",");
        tmp.append(operator<<(QString(""),list[i]));
    }
    tmp.append(")");
    return tmp;
}
template <typename T>
inline QString operator<<(const QString &s, const QVector<T> &vec){QString tmp = s; return operator<<(tmp, vec.toList());}
inline QString operator<<(const QString &s,const QStringList &list) { QString tmp = s;return operator<<(tmp,list.toVector());}
template <class aKey, class aT>
inline QString operator<<(const QString &s, const QMap<aKey, aT> &map){
    QString tmp = s;
    tmp.append(" QMap(");
    for (typename QMap<aKey, aT>::const_iterator it = map.constBegin();
         it != map.constEnd(); ++it) {
        tmp.append('(').append(operator<<(QString(""),it.key())).append(",").append(operator<<(QString(""),it.value())).append(')');
    }
    tmp.append(')');
    return tmp;
}

#endif // BASE_H
