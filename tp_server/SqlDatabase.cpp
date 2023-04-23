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
            "fileType STRING,"
            "fileExtension STRING"
            ")";

    QSqlQuery query;
    query.exec(tblPathCreate);

    if(query.lastError().isValid()) {
        qWarning() << "CREATE TABLE" << query.lastError().text();
        return;
    }
}

QList<QString> ReturnSqlData(const QList<Token> &tokens){
    // Construction de la requête SQL
    QString queryStr = "SELECT * FROM path WHERE ";
    QStringList conditions;
    for (const Token& token : tokens) {
        switch (token.type) {
            case TokenType::FileName:
                conditions.append(QString("filePath LIKE '%%1%'").arg(token.value));
                break;
            case TokenType::FileType:
            if (token.value != "all") {
                conditions.append(QString("fileType = '%1'").arg(token.value));
            }
                break;
            case TokenType::FileExtension:
                if (token.value != "all") {
                conditions.append(QString("fileExtension = '%1'").arg(token.value));
                }
                break;
            case TokenType::MinDate:
                {
                QString dateStr = token.value;
                QDateTime date = QDateTime::fromString(dateStr, "dd/MM/yyyy");
                conditions.append(QString("fileLastModif >= '%1'").arg(date.toString("yyyy-MM-dd")));
                break;
            }
            case TokenType::MaxDate:
                {
                QString dateStr = token.value;
                QDateTime date = QDateTime::fromString(dateStr, "dd/MM/yyyy");
                conditions.append(QString("fileLastModif <= '%1'").arg(date.toString("yyyy-MM-dd")));
            break;
            }
            case TokenType::MinFileSize:
                conditions.append(QString("fileSize >= %1").arg(token.value));
                break;
            case TokenType::MaxFileSize:
                conditions.append(QString("fileSize <= %1").arg(token.value));
                break;
            default:
                break;
        }
    }

    // Ajout des conditions à la requête SQL
    if (!conditions.isEmpty()) {
        queryStr += conditions.join(" AND ");
    } else {
        queryStr += "1"; // retourner tous les résultats si aucun paramètre n'est spécifié
    }

    // Exécution de la requête SQL et récupération des résultats
    QSqlQuery selectQuery(queryStr);
    QList<QString> data;
    while (selectQuery.next()) {
        QString filePath = selectQuery.value(0).toString();
        QString fileSize = selectQuery.value(1).toString();
        QString fileLastModif = selectQuery.value(2).toString();
        QString fileCreated = selectQuery.value(3).toString();
        QString fileType = selectQuery.value(4).toString();
        QString fileExtension = selectQuery.value(5).toString();
        QString rowData = filePath + ", " + fileSize + ", " + fileLastModif + ", " + fileCreated+ ", " + fileType + ", " + fileExtension;
        data.append(rowData);
    }

    return data;
}

