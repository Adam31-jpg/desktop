#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QTcpSocket>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnTxt, &QPushButton::clicked, this, &MainWindow::on_btnTxt_clicked);
    QComboBox *myComboBox = findChild<QComboBox*>("type");
    if (myComboBox) {
        QStringList items = {"image", "text", "exec", "audio", "video", "archive", "unknown", "all"};
        myComboBox->addItems(items);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setListModel(QStringListModel* model)
{
    ui->listView->setModel(model);
}

void MainWindow::on_btnTxt_clicked()
{

    //récuperer les résultat du formulaire
    QString nom_du_fichier = ui->searchTxt->text();
    QString type_du_fichier = ui->type->currentText();
    QString extension_du_fichier = ui->extension->text();
    QString minSize = ui->minSize->text();
    QString maxSize = ui->maxSize->text();
    QString minDate = ui->minDate-> text();
    QString maxDate = ui->maxDate->text();

    qint64 minSizeInt = minSize.toLongLong();
    qint64 maxSizeInt = maxSize.toLongLong();

            QTcpSocket socket;
            socket.connectToHost("localhost", 8080);
            if (!socket.waitForConnected()) {
                qDebug() << "Error: " << socket.errorString();
                return;
            }
            QByteArray data;
            QDataStream out(&data, QIODevice::WriteOnly);
            out << nom_du_fichier << type_du_fichier << extension_du_fichier << minSizeInt << maxSizeInt << minDate << maxDate;
            socket.write(data);
            socket.flush();

            // Attendre la réponse du serveur
            if (socket.waitForReadyRead()) {
                QByteArray receivedData = socket.readAll();
                QDataStream in(&receivedData, QIODevice::ReadOnly);
                QList<QString> folderNames;
                in >> folderNames;
                QStringListModel* model = new QStringListModel(folderNames, this);
                ui->listView->setModel(model);
            } else {
                qDebug() << "Error waiting for data from server";
            }
}

