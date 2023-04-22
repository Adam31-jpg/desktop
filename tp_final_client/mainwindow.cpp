#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QTcpSocket>
#include <QDateTime>
#include <QString>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->searchTxt, SIGNAL(textChanged(QString)), this, SLOT(on_lineEdit_textChanged(QString)));
    connect(ui->btnTxt, &QPushButton::clicked, this, &MainWindow::on_btnTxt_clicked);

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
    QString extention_du_fichier = ui->extention->currentText();
    QString minSize = ui->minSize->text();
    QString maxSize = ui->maxSize->text();
    QString minDate = ui->minDate-> text();
    QString maxDate = ui->maxDate->text();

    QDateTime minDateTime = QDateTime::fromString(minDate, "yyyy/MM/dd");
    QDateTime maxDateTime = QDateTime::fromString(maxDate, "yyyy/MM/dd");

    if (minDateTime.isValid()) {
        // La date n'est pas valide, faites quelque chose pour gérer cette erreur.
        qDebug() << 'non';
    }
    qDebug() << "Nom du fichier : " << nom_du_fichier;
    qDebug() << "Type du fichier : " << type_du_fichier;
    qDebug() << "Extension du fichier : " << extention_du_fichier;
    qDebug() << "Taille minimale : " << minSize;
    qDebug() << "Taille maximale : " << maxSize;
    qDebug() << "Date minimale : " << minDate;
    qDebug() << "Date maximale : " << maxDate;

    // Créer un objet QByteArray pour stocker les données
//        QByteArray data;

//        // Créer un objet QDataStream pour encoder les données dans le tableau de données
//        QDataStream out(&data, QIODevice::WriteOnly);

//        // Écrire les données dans le flux de données
//        out << nom_du_fichier << type_du_fichier << extention_du_fichier << minSize << maxSize << minDate << maxDate;

//        // Envoyer les données au serveur
//        QTcpSocket socket;
//        socket.connectToHost("localhost", 8080);
//        if (socket.waitForConnected())
//        {
//            socket.write(data);
//            socket.waitForBytesWritten();

//            // Attendre une réponse du serveur
//            if (socket.waitForReadyRead()) {
//                QByteArray response = socket.readAll();
//                qDebug() << "Réponse du serveur : " << response;
//            }
//        }
//        else
//        {
//            qDebug() << "Failed to connect to server";
//        }

    QByteArray data;
       QDataStream out(&data, QIODevice::WriteOnly);
       out << nom_du_fichier << type_du_fichier << extention_du_fichier << minSize << maxSize << minDateTime << maxDateTime;


       // Créer un thread pour envoyer les données
       SendThread *sendThread = new SendThread(this);
       sendThread->setData(data);
       sendThread->start();
    QStringList list;

//    // Obtenir la référence de la QListView
    QListView* listView = ui->listView;

//    // Créer un modèle pour la liste
    QStringListModel* model = new QStringListModel(list, this);

//    // Affecter le modèle à la QListView
    listView->setModel(model);

}


