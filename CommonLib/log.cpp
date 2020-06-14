#include "log.h"
#include "common.h"

#include <QString>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QThread>

#include <thread>
#include <mutex>
#include <memory>
#include <map>

namespace Log
{
    static constexpr auto kLogPath = "logs";
    static const QString kLogPrefix = "Log-";
    static const QString kLogSuffix = ".log";
    static std::shared_ptr<QFile> log_file;
    static LogLevel log_level = LogLevel::ERROR;
    static std::mutex log_mtx;
    static std::mutex init_mtx;
    static bool is_inited = false;

    static const std::map<LogLevel, QString> kLogLevelStr =
    {
        {LogLevel::ERROR, "ERROR"},
        {LogLevel::WARNING, "WARNING"},
        {LogLevel::INFO, "INFO"},
        {LogLevel::DEBUG, "DEBUG"},
    };

    static inline const QString &getLogLevelStr(const LogLevel level)
    {
        return kLogLevelStr.at(level);
    }

    bool init(LogLevel level)
    {
        std::lock_guard lock(init_mtx);
        if (is_inited)
            return true;
        else
        {
            log_level = level;
            QDir dir(kLogPath);
            if (!dir.exists())
                if (!dir.mkdir(kLogPath))
                    return false;
            QDateTime time = QDateTime::currentDateTime();
            log_file = std::make_shared<QFile>(QString("./%1/%2%3%4")
                                        .arg(kLogPath)
                                        .arg(kLogPrefix)
                                        .arg(time.toString("hh-mm-ss"))
                                        .arg(kLogSuffix));

            if (!log_file->open(QIODevice::ReadWrite))
                return false;
        }
        return true;
    }

    void addLog(LogLevel level, const QString &log)
    {
        std::lock_guard lock(log_mtx);
        if (init() && EnumToInt(level) <= EnumToInt(log_level))
        {
            QDateTime time = QDateTime::currentDateTime();
            QTextStream stream(log_file.get());
            const QString temp = "%1 [%2](%3) %4"; // time, level, thread_id, log_str;
            stream << temp.arg(time.toString("yy/MM/dd hh:mm:ss"))
                          .arg(getLogLevelStr(level))
                          .arg(getThreadIdStr())
                          .arg(log) << endl;
        }
        else
        {
            qDebug() << "Failed to initialize log module.";
        }
    }
}
