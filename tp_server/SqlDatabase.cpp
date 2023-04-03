#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QDir>
#include "sqldatabase.h"

void SqlConnexion()
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(appDataLocation);
    if(!dir.exists()) {
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }

    QString dbPath = appDataLocation+"/desktop.db";
    qDebug() << "dbPath" << dbPath;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Failed to open database";
        return;
    }

    if(db.lastError().isValid()) {
        qCritical() << "addDatabase" << db.lastError().text();
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
}
