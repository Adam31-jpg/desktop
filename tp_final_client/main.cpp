#include <QApplication>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QStringListModel>
#include <QTcpSocket>
#include <QDataStream>
#include <QDebug>
#include <QThread>
#include "mainwindow.h"

void waitForData(QTcpSocket* socket, MainWindow* window)
{
    while (socket->state() == QAbstractSocket::ConnectedState)
    {
        // Vérifier si de nouvelles données sont disponibles pour la lecture
        if (socket->waitForReadyRead(10000))
        {
            QByteArray receivedData = socket->readAll();

            // Création d'un objet QDataStream pour décoder les données
            QDataStream in(&receivedData, QIODevice::ReadOnly);

            // Lecture de la liste des noms de dossiers envoyée par le serveur
            QList<QString> folderNames;
            in >> folderNames;

            // Créer un modèle pour la liste
            QStringListModel* model = new QStringListModel(window);

            // Ajouter les noms de dossiers au modèle
            model->setStringList(folderNames);

            // Affecter le modèle à la QListView
            window->setListModel(model);

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

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QTcpSocket socket;

    // Connexion à l'hôte distant
    socket.connectToHost("localhost", 8080);

    // Attente de la connexion
    if (socket.waitForConnected(1000))
    {
        qDebug() << "Connected to server";

        // Lancement de la boucle principale dans un thread séparé
        QThread* thread = new QThread;
        QObject::connect(thread, &QThread::started, [&socket, &w]() { waitForData(&socket, &w); });
        thread->start();
    }
    else
    {
        qDebug() << "Could not connect to server";
    }

    return a.exec();
}
