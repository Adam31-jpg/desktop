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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Créer un socket et se connecter à l'hôte distant
    QTcpSocket socket;
    socket.connectToHost("localhost", 8080);
    if (!socket.waitForConnected()) {
        qDebug() << "Error: " << socket.errorString();
        return 1;
    }
    return a.exec();
}

