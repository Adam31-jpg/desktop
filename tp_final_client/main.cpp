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

void waitForData(QTcpSocket* socketPtr, MainWindow* window)
{
    // Créer un objet QTcpSocket pour ce thread
    QTcpSocket socket;
    socket.moveToThread(qApp->thread()); // déplacer l'objet socket dans le thread courant

    // Connexion à l'hôte distant
    socket.connectToHost("localhost", 8080);

    // Attente de la connexion
    if (socket.waitForConnected(1000))
    {
        qDebug() << "Connected to server";

        do {
            if (socket.waitForReadyRead())
            {
                QByteArray receivedData = socket.readAll();

                QDataStream in(&receivedData, QIODevice::ReadOnly);

                QList<QString> folderNames;
                in >> folderNames;

                qDebug() << "Received data from server:" << folderNames;

                QStringListModel* model = new QStringListModel(window);
                model->setStringList(folderNames);
                window->setListModel(model);
            }
            else
            {
                qDebug() << "Waiting for data from server...";
            }
        } while (socket.state() == QAbstractSocket::ConnectedState);

        qDebug() << "Disconnected from server";
    }
    else
    {
        qDebug() << "Could not connect to server";
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Création de la socket et connexion du signal started de QThread à une lambda qui appelle waitForData
    QTcpSocket socket;
    QThread* thread = new QThread;
    QObject::connect(thread, &QThread::started, [&socket, &w]() { waitForData(&socket, &w); });

    thread->start();

    return a.exec();
}
