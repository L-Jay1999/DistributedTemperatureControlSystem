#ifndef LOG_H
#define LOG_H

#include <QString>

namespace Log
{
    enum class LogLevel
    {
        ERROR = 0,
        WARNING,
        INFO,
        DEBUG,
    };

    /**
     * @brief 初始化日志模块，当需要指定日志级别时使用
     * @param 日志级别，指定后只显示与之相等或更高级别的日志
     * @return 初始化是否成功
     */
    bool init(LogLevel level = LogLevel::ERROR);

    /**
     * @brief 向日志文件中添加一条日志
     * @param 添加日志的级别
     * @param 日志内容
     */
    void addLog(LogLevel level, const QString &log);
}

#endif // LOG_H
