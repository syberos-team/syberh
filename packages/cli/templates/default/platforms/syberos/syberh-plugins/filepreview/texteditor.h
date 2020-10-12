#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QObject>
#include <QAbstractListModel>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>

#define CONTENT_LENGTH_PER_PAGE 5 * 1024 //5k

class AsyncPaginater : public QThread
{
    Q_OBJECT
public:
    AsyncPaginater(QString path, QString codecName, QObject *parent = 0) : QThread(parent),
    m_path(path), m_codec(codecName), running(false)
    {
    }
    void run() { //完成分页操作
        QFile file(m_path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        running = true;
        QTextStream in(&file);
        in.setCodec(m_codec.toLocal8Bit().data());
        int page = 0;

        while (running) {
            in.read(CONTENT_LENGTH_PER_PAGE);
            if (!in.atEnd()) {
                page ++;
                emit pagesChanged(page, in.pos());
                qDebug() << "------- paging:" << page;
            } else
                break;
        }

        file.close();
    }
    bool isRunning() const {return running;}
    void stop() { running  = false; }
signals:
    void pagesChanged(int page, qint64 positon);

private:
    QString m_path;
    QString m_codec;
    bool running;
};

class TextEditor : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(int pageCount READ pageCount NOTIFY pageCountChanged)

public:
    explicit TextEditor(QObject *parent = 0);
    ~TextEditor();

    enum TxtRoles {
        ContentRole = Qt::UserRole + 1,
    };

    Q_INVOKABLE QString getContent(int page) const;

    void setPath(QString path);
    QString path() { return m_path; }
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    int pageCount() { return pages.count(); }

signals:
    //void pagingFinished();
    void pageCountChanged();
    void pathChanged();

public slots:
    void save(int page, QString content);
    void setPages(int page, qint64 positon);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    void paging();
    void asyncPaging();

    QList<qint64> pages;
    QString m_path;
    QString codec;
    AsyncPaginater *paginater;

};

#endif // TEXTEDITOR_H