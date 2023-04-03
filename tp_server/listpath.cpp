#include <QDateTime>
#include <QFileInfo>
#include <QList>
#include <QString>
#include <QDir>

struct FileInfo {
    QString filePath;
    QString extension;
    qint64 fileSize;
    QDateTime lastModified;
    QDateTime created;
};

QList<FileInfo> listFileInfo(const QString& path)
{
    QDir dir(path);

    QList<FileInfo> fileInfos;

    // Récupération de la liste de tous les fichiers et répertoires dans le répertoire courant
    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    // Parcours de chaque fichier
    foreach(QFileInfo entry, entries)
    {
        // Récupération des informations du fichier
        QString filePath = entry.absoluteFilePath();
        QString extension = entry.suffix();
        qint64 fileSize = entry.size();
        QDateTime lastModified = entry.lastModified();
        QDateTime created = entry.birthTime();

        // Création de la structure FileInfo et ajout à la liste
        FileInfo fileInfo = { filePath, extension, fileSize, lastModified, created };
        fileInfos.append(fileInfo);
    }

    return fileInfos;
}

