#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QThread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    bool connected = false;

    QTcpSocket socket;
    while (!connected) {
        socket.connectToHost("localhost", 8080);
        connected = socket.waitForConnected(1000); // Attendre jusqu'à 1 seconde
    }

    if (socket.waitForConnected())
    {
        qDebug() << "Connected to server";

        // Boucle principale
        while (socket.state() == QAbstractSocket::ConnectedState)
        {
            // Vérifier si de nouvelles données sont disponibles pour la lecture
            if (socket.waitForReadyRead(10000))
            {
                QByteArray receivedData = socket.readAll();

                // Création d'un objet QDataStream pour décoder les données
                QDataStream in(&receivedData, QIODevice::ReadOnly);

                // Lecture de la liste des noms de dossiers envoyée par le serveur
                QList<QString> folderNames;
                in >> folderNames;

                // Affichage des noms de dossiers
                for (const QString& folderName : folderNames)
                {
                    qDebug() << folderName;
                }
            }
            else
            {
                qDebug() << "Waiting for data from server";
                // Ajouter un délai pour éviter un blocage infini
                QThread::msleep(100);
            }
        }

        qDebug() << "Disconnected from server";
        socket.disconnectFromHost();
        socket.waitForDisconnected();
    }
    else
    {
        qDebug() << "Could not connect to server";
    }

    return a.exec();
}
