#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include "SqlDatabase.h"
#include "listpath.h"
#include <QString>
#include <QDateTime>
#include "lexer.h"
#include "inputvalidator.h"

void handleNewConnection(QTcpServer* server)
{
    while (server->hasPendingConnections())
    {
        QTcpSocket* client = server->nextPendingConnection();
        qDebug() << "New client connected";

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        QString username = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).section(QDir::separator(), -1);
        QString userDatabasePath = username + "/tp_server/desktop.db";
        QFile file(userDatabasePath);
        if (file.size() <= 20000) {
            // File size is less than or equal to 200 bytes, call the function to create it
            listFileInfo(username);
        }

        // Attente de la réception des données
        if (client->waitForReadyRead()) {

            // Lecture des données envoyées par le client
            QByteArray receivedData = client->readAll();

            // Conversion des données reçues en une chaîne de caractères
            QDataStream in(&receivedData, QIODevice::ReadOnly);

            // Extraction des données à partir de QDataStream
            QString input;
            in >> input;

            Lexer lexer(input);
            QVector<Token> tokens = lexer.tokenize();
            QList<QString> folderNames = ReturnSqlData(tokens);
            out << folderNames;
            // Envoi de la liste des noms de dossiers au client
            client->write(block);
        }
        else {
            qDebug() << "Error waiting for data from client";
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SqlConnexion();

    QTcpServer server;

    if (!server.listen(QHostAddress::Any, 8080))
    {
        qDebug() << "Server could not start!";
        return 1;
    }

    qDebug() << "Server started";

    QObject::connect(&server, &QTcpServer::newConnection, [&server](){handleNewConnection(&server);});

    return a.exec();
}
