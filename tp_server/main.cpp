#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

QList<QString> listFolders(const QString& path)
{
    QDir dir(path);
    QList<QString> folderNames;
    // Récupération de la liste de tous les fichiers et répertoires dans le répertoire courant
    QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    // Parcours de chaque fichier ou répertoire
    foreach(QFileInfo entry, entries)
    {
        if (entry.isDir()) {
            // S'il s'agit d'un répertoire, on l'ajoute à la liste
            folderNames << entry.absoluteFilePath();
            // On appelle récursivement la fonction pour explorer les sous-répertoires
//            QList<QString> subFolderNames = listFolders(entry.absoluteFilePath());
//            folderNames.append(subFolderNames);
        }
    }
    qDebug() << folderNames;
    return folderNames;
}

void handleNewConnection(QTcpServer* server)
{
    while (server->hasPendingConnections())
    {
        QTcpSocket* client = server->nextPendingConnection();
        qDebug() << "New client connected";

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);

        QList<QString> folderNames = listFolders("c:/");
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
