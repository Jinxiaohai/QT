/****************************************************************************
**  @copyright  TinKinG
**  @contract   lsnbing@126.com
**
**  @brief  日志模块
**  @file   log.h
**  @author TinKinG
**  @date   2016-06-07
**
**
*****************************************************************************/

#ifndef TKG_LOG_H_
#define TKG_LOG_H_
#endif

#include <string>

#define TKGON 1
#define TKGOFF 0

#define TKG_LOG_FILE_DEBUG    TKGON//是否写到文件中
#define TKG_CONSOLE_DEBUG     TKGON//是否输出到终端
#define TKG_QT_DEBUG          TKGON//是否用Qt的qDebug输出,否则用printf输出
#define TKG_DETAIL_DEBUG      TKGON//是否输出行号信息
#define LOG_LENGTH 4096

typedef enum {
    LEVEL_ERROR,
    LEVEL_WARNING,
    LEVEL_INFO
} LevelType;

#ifdef Q_CC_GNU
#   define TKGwrite_log( fmt,args...) TKGLog::Instance()->write_log(fmt, __FILE__, __LINE__, ##args)

#   define LTerror TKGLog::Instance()->set_level(LevelType::LEVEL_ERROR)
#   define LTwarning TKGLog::Instance()->set_level(LevelType::LEVEL_WARNING)
#   define LTinfo TKGLog::Instance()->set_level(LevelType::LEVEL_INFO)

#   define TKGwrite_log_info(fmt,args...) {LTinfo; TKGwrite_log(fmt,##args);}
#   define TKGwrite_log_error(fmt,args...) {LTerror; TKGwrite_log(fmt,##args);}
#   define TKGwrite_log_warning(fmt,args...) {LTwarning; TKGwrite_log(fmt,##args);}
#else
#   define TKGwrite_log( fmt,...) TKGLog::Instance()->write_log(fmt, __FILE__, __LINE__, __VA__ARGS__)

#   define LTerror TKGLog::Instance()->set_level(LevelType::LEVEL_ERROR)
#   define LTwarning TKGLog::Instance()->set_level(LevelType::LEVEL_WARNING)
#   define LTinfo TKGLog::Instance()->set_level(LevelType::LEVEL_INFO)

#   define TKGwrite_log_info(fmt,...) {LTinfo; TKGwrite_log(fmt,__VA__ARGS__);}
#   define TKGwrite_log_error(fmt,...) {LTerror; TKGwrite_log(fmt,__VA__ARGS__);}
#   define TKGwrite_log_warning(fmt,...) {LTwarning; TKGwrite_log(fmt,__VA__ARGS__);}
#endif

class QMutex;
class TKGLog {
private:
    static const char LOG_ERROR[][4];

    static TKGLog * _instance;
    LevelType m_level;
    std::string m_file_name;
    FILE * m_file;
    QMutex * m_cs;

    TKGLog();
    bool createAbsoluteDir(const QString &dir_name="");
    std::string get_current_date();
    std::string get_current_time();
    void print_log( const char* msg );//输出到文件，同时可添加输出到其他如数据库等等
public:
    /**
     * 用法：
     * 1. 实例化：TKGLog::Instance();或TKGLog::Instance().set_file_name("mylog");
     * 2. 设置文件名：set_file_name("mylog");//或者为空，TKG2016-12-7mylog.log
     * 3. 使用宏进行输出
    */
    virtual ~TKGLog();
    static TKGLog* Instance();
    void set_file_name( const std::string & file_name );

    static std::string safety_str( const char * );
    void set_level( LevelType level );
    void  write_log(const char *format,const char * file_name,int line, ... );
};

