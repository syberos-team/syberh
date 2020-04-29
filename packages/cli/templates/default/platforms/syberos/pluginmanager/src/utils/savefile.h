#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QTemporaryFile>

#include <memory>

namespace Utils {

class SaveFile : public QFile
{
    Q_OBJECT

public:
    explicit SaveFile(const QString &filename);
    ~SaveFile() override;

    bool open(OpenMode flags = QIODevice::WriteOnly) override;

    void rollback();
    bool commit();

    static void initializeUmask();

private:
    const QString m_finalFileName;
    QScopedPointer<QTemporaryFile> m_tempFile;
    bool m_finalized = true;
    static QFile::Permissions m_umask;
};

} // namespace Utils

#endif // SAVEFILE_H
