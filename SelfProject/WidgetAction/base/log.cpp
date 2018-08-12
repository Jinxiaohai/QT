#include <QtGlobal>
#ifdef QT_VERSION
#   include <QMutex>
#   include <QDir>
#   include <QDebug>
#else

#endif

#include <ctime>
#include <cstdarg>
#include <cstdio>
#include "assert.h"
#include "log.h"

TKGLog * TKGLog::_instance = 0;
const char TKGLog::LOG_ERROR[][4] = {"ERR","WAR","INF"};

std::string TKGLog::safety_str( const char * msg) {
    const int cut = 128;
    unsigned int count = LOG_LENGTH - cut;//963个
    if( strlen( msg ) > count ) {
        std::string str( msg,LOG_LENGTH-cut);
        str += "...";
        return str;
    }
    std::string str( msg );
    return str;
}

TKGLog * TKGLog::Instance() {
    //这里不用加锁，可以通过启动时，统一初始化，这样不用为以后多次调用产生性能延迟
    if( !_instance ) {
        _instance = new TKGLog();
    }
    return _instance;
}

bool TKGLog::createAbsoluteDir(const QString &absolu_dir){
    QDir dir;
    if(dir.exists(absolu_dir))
        return true;
#ifdef Q_OS_WIN32
    QStringList list = absolu_dir.split("\\");
    QString mid = "\\";
#else
    QStringList list = absolu_dir.split("/");
    QString mid = "/";
#endif
    QString path("");
    for(QStringList::const_iterator it = list.begin(); it != list.end(); ++it){
        path += *it;
        path += mid;
        if(!dir.exists(path))
            if(!dir.mkdir(path)){
                qDebug() << "create error!" << path;
                return false;
            }

    }
    return true;
}

static const std::string getLogFilePath(){
#ifdef Q_OS_WIN32
    return std::string((QDir::currentPath()+"\\logs\\").toStdString().c_str());
#else
    return std::string((QDir::currentPath()+"/logs/").toStdString().c_str());
#endif
}

TKGLog::TKGLog(){
    m_level = LevelType::LEVEL_INFO;
    m_file = 0;
    m_cs = new QMutex();
}

TKGLog::~TKGLog() {
    if( m_file )
        fclose( m_file );
    if(m_cs){
        delete m_cs;
        m_cs = 0;
    }
}

void TKGLog::print_log( const char* msg ) {
    m_cs->lock();

#if TKG_CONSOLE_DEBUG  //终端调试开关
#   if(TKG_QT_DEBUG)
    qDebug() << msg;
#   else
    printf( "%s\n", msg );
#   endif
#endif

#if TKG_LOG_FILE_DEBUG    //文件调试开关
    fprintf( m_file, "%s\n", msg );
    fflush( m_file );//强刷
#endif
    m_cs->unlock();
}

void TKGLog::set_file_name( const std::string & file_name ) {
    m_cs->lock();
    if( 0 == m_file ) {
        m_file_name = getLogFilePath();
        QDir dir;
        if(!dir.exists(m_file_name.c_str())){
            dir.mkdir(QString(m_file_name.c_str()));
        }
        m_file_name = m_file_name + std::string("TKG") + get_current_date() + file_name + std::string(".log");
        if( !( m_file = fopen( m_file_name.c_str( ), "a+" ) ) ) {
            printf( "Log File Open Error!!!\n" );
            m_cs->unlock();
            return;
        }
    }
    m_cs->unlock();
}

void TKGLog::set_level( LevelType level ) {
    m_cs->lock();
    m_level = level;
    m_cs->unlock();
}

std::string TKGLog::get_current_date() {
    time_t t = time( 0 );
    char tmp[16];
    struct tm result;
#ifdef Q_OS_WIN32
    localtime_s( &result, &t );//use of windows
#else
    localtime_r(&t,&result);//use of *nix systems
#endif
    strftime( tmp, sizeof( tmp ), "%Y-%m-%d", &result );
    return tmp;
}
std::string TKGLog::get_current_time() {
    time_t t = time( 0 );
    char tmp[16];
    struct tm result;
#ifdef Q_OS_WIN32
    localtime_s( &result, &t );
#else
    localtime_r(&t,&result);
#endif
    strftime( tmp, sizeof( tmp ), "%X", &result );
    return tmp;
}

//输出范例：[2015-10-20 17:06] [Error] [Log.cpp @ 123] [打开文件错误]
void  TKGLog::write_log( const char* format, const char * file_name, int line_h, ... ) {
    //assert(m_file);
    char msg[LOG_LENGTH + 256] = { '\0' };
    strcat( msg, "[" );
    strcat( msg, get_current_date().c_str() );
    strcat( msg, " " );
    strcat( msg, get_current_time().c_str() );
    strcat( msg, "] [" );

    strcat( msg, LOG_ERROR[m_level] );
    strcat( msg, "] " );

#if TKG_DETAIL_DEBUG
    strcat( msg, "[ " );
    strcat( msg, file_name );
    strcat( msg, " : " );
    char line[16];
    sprintf( line, "%d ", line_h );
    strcat( msg, line );
    strcat( msg, "]\t" );
#endif

    char buf[LOG_LENGTH];
    va_list argp;
    va_start( argp, line_h );
    vsnprintf( buf, sizeof( buf ), format, argp );
    va_end( argp );
    strcat( msg, buf );

    print_log( msg );
}
