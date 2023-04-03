#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QDir>
#include "sqldatabase.h"

void SqlConnexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if(db.lastError().isValid()) {
        qCritical() << "addDatabase" << db.lastError().text();
        return;
    }

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(appDataLocation);
    if(!dir.exists()) {
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }

    QString dbPath = appDataLocation+"/desktop.db";
    qDebug() << "dbPath" << dbPath;
    db.setDatabaseName(dbPath);
    if(!db.open()) {
        qCritical() << "Unable to open db" << db.lastError().text() << dbPath;
        return;
    }

    QString tblPathCreate = "CREATE TABLE IF NOT EXISTS path ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "filePath STRING,"
            "fileSize BIGINT,"
            "fileLastModif BIGINT,"
            "fileCreated BIGINT,"
            "fileExtension STRING"
            ")";

    QSqlQuery query;
    query.exec(tblPathCreate);

    if(query.lastError().isValid()) {
        qWarning() << "CREATE TABLE" << query.lastError().text();
        return;
    }

    const int INSERTS_COUNT=10;
    for(int i=0; i<= INSERTS_COUNT; i++) {
        QString sqlInsert = QString("INSERT INTO path (filePath, fileSize, fileLastModif, fileCreated, fileExtension) "
                                    "VALUES('file%1', %2, %3, %4, 'file%5')")
                                    .arg(i).arg(i).arg(i).arg(i).arg(i);
        query.exec(sqlInsert);

        if(query.lastError().isValid()) {
            qWarning() << "INSERT PATH" << query.lastError().text();
            return;
        }
    }
}

