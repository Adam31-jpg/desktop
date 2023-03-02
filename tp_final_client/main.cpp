#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool connected = false;

    QTcpSocket socket;
    while (!connected) {
        socket.connectToHost("localhost", 8080);
        connected = socket.waitForConnected(1000); // Attendre jusqu'à 1 seconde
    }

    if (socket.waitForConnected())
    {
        qDebug() << "Connected to server";

        QDataStream in(&socket);
        in.startTransaction();

        if (in.device()->bytesAvailable() > 0)
        {
            QList<QString> folderNames;
            in >> folderNames;

            if (in.commitTransaction())
            {
                qDebug() << "Folder names:";
                foreach(QString folderName, folderNames)
                {
                    qDebug() << folderName;
                }
            }
            else
            {
                qDebug() << "Failed to receive folder names";
            }
        }

        while (socket.state() == QAbstractSocket::ConnectedState && socket.waitForReadyRead())
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

//        socket.disconnectFromHost();
//        socket.waitForDisconnected();
    }
    else
    {
        qDebug() << "Could not connect to server";
    }

    return a.exec();
}
