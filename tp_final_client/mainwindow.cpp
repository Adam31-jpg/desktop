#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnTxt_clicked()
{
//    QStringList list;

//    for(int i = 0; i < 1000; i++){
//        list.append(QString::number(i));
//    }

//    // Obtenir la référence de la QListView
//    QListView* listView = ui->listView;

//    // Créer un modèle pour la liste
//    QStringListModel* model = new QStringListModel(list, this);

//    // Affecter le modèle à la QListView
//    listView->setModel(model);

//    // Connecter le signal textChanged() du QLineEdit à la fonction on_lineEdit_textChanged()
//    connect(ui->searchTxt, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_textChanged);
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    // Obtenir le modèle de la QListView
    QAbstractItemModel* model = ui->listView->model();

    if(model) {
        QStringList list;

        // Parcourir la liste d'éléments du modèle et ajouter les éléments qui contiennent le texte filtré
        for(int i = 0; i < model->rowCount(); i++) {
            QModelIndex index = model->index(i, 0);
            QString itemText  = model->data(index, Qt::DisplayRole).toString();

            if(itemText .contains(text, Qt::CaseInsensitive)) {
                list.append(itemText);
            }
        }

        // Mettre à jour la liste filtrée dans le modèle de la QListView
        QStringListModel* stringListModel = qobject_cast<QStringListModel*>(model);
        if(stringListModel) {
            stringListModel->setStringList(list);
        }
    }
}




