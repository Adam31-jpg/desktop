#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include "SqlDatabase.h"
#include "listpath.h"


void handleNewConnection(QTcpServer* server)
{
    while (server->hasPendingConnections())
    {
        QTcpSocket* client = server->nextPendingConnection();
        qDebug() << "New client connected";

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);

        QList<QString> folderNames = listFileInfo("c:/users/florian/launcher");
        out << folderNames;

        // Envoi de la liste des noms de dossiers au client
        client->write(block);

        // Attente de la confirmation de la réception des données
        if (!client->waitForBytesWritten()) {
            qDebug() << "Error sending data to client";
        }

//            client->disconnectFromHost();
//            client->deleteLater();
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
