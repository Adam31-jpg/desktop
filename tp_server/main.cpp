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

        // Attente de la réception des données
        if (client->waitForReadyRead()) {

            // Lecture des données envoyées par le client
            QByteArray receivedData = client->readAll();

            // Conversion des données reçues en une chaîne de caractères
            QDataStream in(&receivedData, QIODevice::ReadOnly);

            // Extraction des données à partir de QDataStream
            QString nom_du_fichier;
            QString type_du_fichier;
            QString extension_du_fichier;
            qint64 minSize, maxSize;
            QString minDate, maxDate;
            in >> nom_du_fichier >> type_du_fichier >> extension_du_fichier >> minSize >> maxSize >> minDate >> maxDate;

            QString input = nom_du_fichier + ";" + type_du_fichier + ";" + extension_du_fichier + ";" +
                            QString::number(minSize) + ";" + QString::number(maxSize) + ";" + minDate + ";" + maxDate;

            Lexer lexer(input);
            QVector<Token> tokens = lexer.tokenize();
            QList<QString> folderNames = ReturnSqlData(tokens);

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            qDebug() << "folderNames" << folderNames;
            out << folderNames;
            qDebug() << "out" << folderNames;
            client->waitForBytesWritten(); // Attendre la fin de l'envoi des données
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
