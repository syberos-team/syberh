#include <QProcess>
#include <QFileInfo>
#include "texteditor.h"

TextEditor::TextEditor(QObject *parent) :
    QAbstractListModel(parent), m_path(""), paginater(0)
{
}

TextEditor::~TextEditor()
{
    if (paginater && paginater->isRunning()) {
        paginater->stop();
        paginater->wait();
    }
}

void TextEditor::asyncPaging()
{
    pages.clear();
    pages << 0;

    if (paginater && paginater->isRunning()) {
        paginater->stop();
        paginater->wait();
    }
    paginater = new AsyncPaginater(m_path, codec, this);
    connect(paginater, SIGNAL(pagesChanged(int,qint64)),
            this, SLOT(setPages(int,qint64)));
    //connect(paginater, &AsyncPaginater::finished, paginater, &QObject::deleteLater);
    paginater->start();
}

void TextEditor::setPages(int page, qint64 positon)
{
    qDebug() << Q_FUNC_INFO << "set pages:" << page << positon;
    if(page < pages.count())
        pages.replace(page, positon);
    else if(page == pages.count()) {
        pages.append(positon);
        emit pageCountChanged();
    }
    else {
        qDebug() << Q_FUNC_INFO << "paging error:" << page << positon;
        return;
    }
}

void TextEditor::paging()
{
    pages.clear();
    pages << 0;
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    in.setCodec(codec.toLocal8Bit().data());
    while (!in.atEnd()) {
        in.read(CONTENT_LENGTH_PER_PAGE);
        pages << in.pos();
        qDebug() << pages.size() << pages.last() << file.pos();
    }
    file.close();

    qDebug() << Q_FUNC_INFO << " page num:" << pages.count();
}

void TextEditor::setPath(QString path)
{
    if(path.isEmpty()){
        return;
    }
    if(path.startsWith("file://")){
        m_path = path.mid(7);
    }else{
        m_path = path;
    }

    QProcess process;
    process.start("/usr/bin/enca -L zh_CN " + QString("\"") + m_path + QString("\""));
    process.waitForFinished(-1);
    QString stdout = process.readAllStandardOutput();
    QStringList re = stdout.split("\n").at(0).split(";");
    if (re.count() > 1) {
        codec = re.at(1).simplified();
    } else {
        codec = "UTF-8";
    }

    asyncPaging();

    emit pathChanged();

    qDebug() << Q_FUNC_INFO << " codec:" << m_path << codec;
}

void TextEditor::save(int page, QString content)
{
    QFile file(m_path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&file);
    in.setCodec(codec.toLocal8Bit().data());
    in.seek(0);
    QString before = in.read(page * CONTENT_LENGTH_PER_PAGE);

    QString after = "";
    if (page < pages.count()-1) {
        qint64 pos = pages.at(page+1);
        in.seek(pos);
        after = in.read((pages.count() - page) * CONTENT_LENGTH_PER_PAGE);
    }
    file.resize(0);
    in << before << content << after;
    file.close();

    //paging();
    asyncPaging();

    qDebug() << Q_FUNC_INFO << "save done";
}

QString TextEditor::getContent(int page) const
{
    qDebug() << Q_FUNC_INFO << " page:" << page << m_path;
    if(m_path.isEmpty()){
        return "";
    }

    if (page < 0 || page >= pages.count()) {
        qDebug() << Q_FUNC_INFO << "wrong page number." << page << pages.count();
        return "";
    }
    if (m_path.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "file path is emputy.";
        return "";
    }

    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << Q_FUNC_INFO << "can't open file." << m_path;
        return "";
    }

    qint64 pos = 0;
    if(!pages.isEmpty())
        pos = pages.at(page);

    QTextStream in(&file);
    in.setCodec(codec.toLocal8Bit().data());
    in.seek(pos);
    QString re = in.read(CONTENT_LENGTH_PER_PAGE);

    file.close();
    qDebug() << Q_FUNC_INFO << " pos:" << pos;
    return re;
}

QHash<int, QByteArray> TextEditor::roleNames() const
{
    static QHash<int, QByteArray> roles;

    if (roles.isEmpty()) {
        roles[ContentRole] = "contentText";
    }

    return roles;
}

int TextEditor::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return pages.count();
}

QVariant TextEditor::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= pages.count())
        return QVariant();

    switch (role) {
    case ContentRole:
        return getContent(index.row());
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags TextEditor::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TextEditor::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if (role == ContentRole) { //Qt::EditRole) {
        save(index.row(), value.toString());

        return true;
    }

    return false;
}
