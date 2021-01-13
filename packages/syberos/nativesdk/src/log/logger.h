#ifndef LOGGER_H
#define LOGGER_H

#include "log_global.h"

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QMap>
#include <QHash>
#include <QList>
#include <QVector>
#include <QSet>
#include <QContiguousCache>

#include <iostream>
#include <vector>
#include <list>
#include <map>

namespace Log {

namespace Internal {

class LoggerPrivate;

}   // namespace Internal


class LOG_EXPORT Logger
{
public:
    enum Level {
      LV_DEBUG, LV_INFO, LV_WARN, LV_ERROR
    };

    Logger(Level level,
           const char *file, size_t filelen,
           const char *func, size_t funclen,
           long line);
    virtual ~Logger();

    bool isDebugEnabled();
    bool isInfoEnabled();
    bool isWarningEnabled();
    bool isErrorEnabled();

    inline Logger &condition(bool cond) { m_whetherToLog = cond; return *this; }

    static void setCategory(const QString &category);
    static void setCategory(const char *category);
    static void clean();

    inline bool autoInsertSpaces() const { return m_space; }
    inline void setAutoInsertSpaces(bool b) { m_space = b; }

    inline Logger &space() { m_space = true; m_ts << ' '; return *this; }
    inline Logger &nospace() { m_space = false; return *this; }
    inline Logger &maybeSpace() { if(m_space) m_ts << ' '; return *this; }

    inline Logger &operator<<(QChar t) { if(!m_whetherToLog) return *this; putUcs4(t.unicode()); return maybeSpace(); }
    inline Logger &operator<<(bool t) { if(!m_whetherToLog) return *this; m_ts << (t ? "true" : "false"); return maybeSpace(); }
    inline Logger &operator<<(char t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(signed short t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(unsigned short t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(char16_t t) { if(!m_whetherToLog) return *this; return *this << QChar(ushort(t)); }
    inline Logger &operator<<(char32_t t) { if(!m_whetherToLog) return *this; putUcs4(t); return maybeSpace(); }
    inline Logger &operator<<(signed int t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(unsigned int t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(signed long t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(unsigned long t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(qint64 t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(quint64 t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(float t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(double t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(const char* t) { if(!m_whetherToLog) return *this; m_ts << QString::fromUtf8(t); return maybeSpace(); }
    inline Logger &operator<<(const QString & t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(const QStringRef & t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    inline Logger &operator<<(QStringView s) { if(!m_whetherToLog) return *this; m_ts << s; return maybeSpace(); }
#endif
    inline Logger &operator<<(QLatin1String t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(const QByteArray & t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(const void * t) { if(!m_whetherToLog) return *this; m_ts << t; return maybeSpace(); }
    inline Logger &operator<<(std::nullptr_t) { if(!m_whetherToLog) return *this; m_ts << "(nullptr)"; return maybeSpace(); }
    inline Logger &operator<<(QTextStreamFunction f) { if(!m_whetherToLog) return *this; m_ts << f; return *this;}
    inline Logger &operator<<(QTextStreamManipulator m) { if(!m_whetherToLog) return *this; m_ts << m; return *this; }

    template <typename T>
    inline Logger &operator<<(const QSet<T> &set) { return printSequentialContainer("QSet", set); }

    template <class T>
    inline Logger &operator<<(const QList<T> &list) { return printSequentialContainer("QList", list); }

    template <typename T>
    inline Logger &operator<<(const QVector<T> &vec) { return printSequentialContainer("QVector", vec); }

    template <typename T, typename Alloc>
    inline Logger &operator<<(const std::vector<T, Alloc> &vec) { return printSequentialContainer("std::vector", vec); }

    template <typename T, typename Alloc>
    inline Logger &operator<<(const std::list<T, Alloc> &vec) { return printSequentialContainer("std::list", vec); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    inline Logger &operator<<(const std::map<Key, T, Compare, Alloc> &map) { return printSequentialContainer("std::map", map); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    inline Logger &operator<<(const std::multimap<Key, T, Compare, Alloc> &map) { return printSequentialContainer("std::multimap", map); }

    template <class Key, class T>
    inline Logger &operator<<(const QMap<Key, T> &map)
    {
        if(!m_whetherToLog)
            return *this;
        const bool oldSetting = autoInsertSpaces();
        nospace() << "QMap(";
        for (typename QMap<Key, T>::const_iterator it = map.constBegin();
             it != map.constEnd(); ++it) {
            m_ts << '(' << it.key() << "=" << it.value() << ')';
        }
        m_ts << ')';
        setAutoInsertSpaces(oldSetting);
        return maybeSpace();
    }

    template <class Key, class T>
    inline Logger &operator<<(const QHash<Key, T> &hash)
    {
        if(!m_whetherToLog)
            return *this;
        const bool oldSetting = autoInsertSpaces();
        nospace() << "QHash(";
        for (typename QHash<Key, T>::const_iterator it = hash.constBegin();
                it != hash.constEnd(); ++it)
            m_ts << '(' << it.key() << "=" << it.value() << ')';
        m_ts << ')';
        setAutoInsertSpaces(oldSetting);
        return maybeSpace();
    }

    template <class T1, class T2>
    inline Logger &operator<<(const QPair<T1, T2> &pair)
    {
        if(!m_whetherToLog)
            return *this;
        const bool oldSetting = autoInsertSpaces();
        nospace() << "QPair(" << pair.first << ',' << pair.second << ')';
        setAutoInsertSpaces(oldSetting);
        return maybeSpace();
    }

    template <class T1, class T2>
    inline Logger &operator<<(const std::pair<T1, T2> &pair)
    {
        if(!m_whetherToLog)
            return *this;
        const bool oldSetting = autoInsertSpaces();
        nospace() << "std::pair(" << pair.first << ',' << pair.second << ')';
        setAutoInsertSpaces(oldSetting);
        return maybeSpace();
    }

    template <class T>
    inline Logger &operator<<(const QContiguousCache<T> &cache)
    {
        if(!m_whetherToLog)
            return *this;
        const bool oldSetting = autoInsertSpaces();
        nospace() << "QContiguousCache(";
        for (int i = cache.firstIndex(); i <= cache.lastIndex(); ++i) {
            m_ts << cache[i];
            if (i != cache.lastIndex())
                m_ts << ", ";
        }
        m_ts << ')';
        setAutoInsertSpaces(oldSetting);
        return maybeSpace();
    }

private:
    Internal::LoggerPrivate *d = nullptr;
    QTextStream m_ts;
    QString m_buffer;
    bool m_whetherToLog = true;
    bool m_space = true;

    void end();
    void putUcs4(uint ucs4);

    template <typename SequentialContainer>
    inline Logger &printSequentialContainer(const char *which, const SequentialContainer &c)
    {
        if(!m_whetherToLog)
            return *this;
        const bool oldSetting = autoInsertSpaces();
        nospace() << which << '(';
        typename SequentialContainer::const_iterator it = c.begin(), end = c.end();
        if (it != end) {
            m_ts << *it;
            ++it;
        }
        while (it != end) {
            m_ts << ", " << *it;
            ++it;
        }
        m_ts << ')';
        setAutoInsertSpaces(oldSetting);
        return maybeSpace();
    }
};


#define LOGGER(lv) Logger(lv, __FILE__, sizeof(__FILE__)-1, Q_FUNC_INFO, sizeof(Q_FUNC_INFO)-1, __LINE__)

#define sDebug LOGGER(Log::Logger::LV_DEBUG)
#define sDebugc(cond) sDebug.condition(cond)

#define sInfo LOGGER(Log::Logger::LV_INFO)
#define sInfoc(cond) sInfo.condition(cond)

#define sWarn LOGGER(Log::Logger::LV_WARN)
#define sWarnc(cond) sWarn.condition(cond)

#define sError LOGGER(Log::Logger::LV_ERROR)
#define sErrorc(cond) sError.condition(cond)

}   // namespace Log
#endif // LOGGER_H
