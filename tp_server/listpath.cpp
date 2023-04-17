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

QList<QString> listFileInfo(const QString& path)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Florian/AppData/Roaming/tp_server/desktop.db");
    if (!db.open()) {
        qDebug() << "Failed to open database";
        return QList<QString>();
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
            QString lastModifiedStr = lastModified.toString("yyyy-MM-dd HH:mm:ss");
            QString createdStr = created.toString("yyyy-MM-dd HH:mm:ss");
            QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO path (filePath, fileSize, fileLastModif, fileCreated, fileExtension) "
                                    "VALUES (:filePath, :fileSize, :fileLastModif, :fileCreated, :fileExtension)");
                insertQuery.bindValue(":filePath", filePath);
                insertQuery.bindValue(":fileSize", fileSize);
                insertQuery.bindValue(":fileLastModif", lastModifiedStr);
                insertQuery.bindValue(":fileCreated", createdStr);
                insertQuery.bindValue(":fileExtension", extension);
                if (!insertQuery.exec()) {
                    qDebug() << "Failed to insert data";
                }
        }
    }
    // Récupération des données de la base de données
    QSqlQuery selectQuery("SELECT * FROM path");
    QList<QString> data;
    while (selectQuery.next()) {
        QString filePath = selectQuery.value(0).toString();
        QString fileSize = selectQuery.value(1).toString();
        QString fileLastModif = selectQuery.value(2).toString();
        QString fileCreated = selectQuery.value(3).toString();
        QString fileExtension = selectQuery.value(4).toString();
        QString rowData = filePath + ", " + fileSize + ", " + fileLastModif + ", " + fileCreated + ", " + fileExtension;
        data.append(rowData);
    }

    return data;
}
