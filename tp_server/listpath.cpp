#include <QDateTime>
#include <QFileInfo>
#include <QList>
#include <QString>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QDir>

void listFileInfo(const QString& path)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString username = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).section(QDir::separator(), -1);
    QString userDatabasePath = username + "/tp_server/desktop.db";
    qDebug() << "Nom d'utilisateur actuel : " << username;
    qDebug() << "Chemin de la base de données : " << userDatabasePath;
    db.setDatabaseName(userDatabasePath);
    if (!db.open()) {
        qDebug() << "Failed to open database";
        return;
    }

    QDir dir(path);

    QList<QString> fileNames;

    // Récupération de la liste de tous les fichiers et répertoires dans le répertoire courant
    QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    // Parcours de chaque fichier ou répertoire
    foreach(QFileInfo entry, entries)
    {
        if (entry.isFile()) {
            // S'il s'agit d'un fichier, on l'ajoute à la liste
            fileNames << entry.absoluteFilePath();
            QString filePath = entry.absoluteFilePath();
            QString extension = entry.suffix();
            qint64 fileSize = entry.size();
            QDateTime lastModified = entry.lastModified();
            QDateTime created = entry.birthTime();
            QString lastModifiedStr = lastModified.toString("yyyy-MM-dd");
            QString createdStr = created.toString("yyyy-MM-dd");
            QString fileType;
            if (extension == "sh" || extension == "jar" || extension == "url"|| extension == "lnk" || extension == "exe") {
                        fileType = "exec";
                    } else if (extension == "txt" || extension == "pdf" || extension == "doc" || extension == "docx" || extension == "json" || extension == "lock") {
                        fileType = "text";
                    } else if (extension == "png" || extension == "jpg" || extension == "gif" || extension == "bmp" || extension == "tif") {
                        fileType = "image";
                    } else if (extension == "mp3") {
                        fileType = "audio";
                    } else if (extension == "mp4" || extension == "avi" || extension == "mov" || extension == "wmv") {
                        fileType = "video";
                    } else if (extension == "zip" || extension == "rar" || extension == "7z" || extension == "tar" || extension == "gz") {
                        fileType = "archive";
                    } else {
                        fileType = "unknown";
                    }
            if(extension == "null") {
                extension = "all";
            }
            QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO path (filePath, fileSize, fileLastModif, fileCreated,fileType, fileExtension) "
                                    "VALUES (:filePath, :fileSize, :fileLastModif, :fileCreated,:fileType, :fileExtension)");
                insertQuery.bindValue(":filePath", filePath);
                insertQuery.bindValue(":fileSize", fileSize);
                insertQuery.bindValue(":fileLastModif", lastModifiedStr);
                insertQuery.bindValue(":fileCreated", createdStr);
                insertQuery.bindValue(":fileType", fileType);
                insertQuery.bindValue(":fileExtension", extension);
                if (!insertQuery.exec()) {
                    qDebug() << "Failed to insert data";
                }
        }
        else if (entry.isDir()) {
                // S'il s'agit d'un dossier, on appelle la fonction récursivement pour parcourir son contenu
                listFileInfo(entry.absoluteFilePath());
            }
    }
}
