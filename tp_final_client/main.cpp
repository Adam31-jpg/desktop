#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;
    socket.connectToHost("localhost", 8080);

    if (socket.waitForConnected())
    {
        qDebug() << "Connected to server";

        QDataStream in(&socket);
        in.startTransaction();

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

        socket.disconnectFromHost();
        socket.waitForDisconnected();
    }
    else
    {
        qDebug() << "Could not connect to server";
    }

    return a.exec();
}
