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
//void handleNewConnection(QTcpServer* server)
//{
//    while (server->hasPendingConnections())
//    {
//        QTcpSocket* client = server->nextPendingConnection();
//        qDebug() << "New client connected";

//        QByteArray block;
//        QDataStream out(&block, QIODevice::WriteOnly);

//        QList<QString> folderNames = listFileInfo("c:/users/florian/launcher");
//        out << folderNames;

//        // Envoi de la liste des noms de dossiers au client
//        client->write(block);

//        // Attente de la confirmation de la réception des données
//        if (!client->waitForBytesWritten()) {
//            qDebug() << "Error sending data to client";
//        }

////            client->disconnectFromHost();
////            client->deleteLater();
//    }
//}
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

        // Attente de la réception des données
            if (client->waitForReadyRead()) {

                // Lecture des données envoyées par le client
                QByteArray receivedData = client->readAll();

                // Conversion des données reçues en une chaîne de caractères
                QDataStream in(&receivedData, QIODevice::ReadOnly);

                // Extraction des données à partir de QDataStream
                QString nom_du_fichier;
                QString type_du_fichier;
                QString extention_du_fichier;
                qint64 minSize, maxSize;
                QString minDate, maxDate;
                in >> nom_du_fichier >> type_du_fichier >> extention_du_fichier >> minSize >> maxSize >> minDate >> maxDate;


                // Utilisation des données extraites
                qDebug() << "Nom du fichier: " << nom_du_fichier;
                qDebug() << "Type du fichier: " << type_du_fichier;
                qDebug() << "Extension du fichier: " << extention_du_fichier;
                qDebug() << "Taille minimale: " << minSize;
                qDebug() << "Taille maximale: " << maxSize;
                qDebug() << "Date minimale: " << minDate;
                qDebug() << "Date maximale: " << maxDate;
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
