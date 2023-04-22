#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QDate>
#include <QThread>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setListModel(QStringListModel* model);

private slots:
    void on_btnTxt_clicked();


private:
    Ui::MainWindow *ui;
    QStringListModel* m_model;
    QStringList m_data;
    QStringList m_filteredData;
    QString m_filepathFilter;
    int m_filesizeFilterMin;
    int m_filesizeFilterMax;
    QDate m_dateLastModifFilter;
    QDate m_dateFilterMin;
    QDate m_dateFilterMax;
    QString m_extensionTypeFilter;
    QString m_extensionFilter;
    void updateFilter();
};

class SendThread : public QThread
{
    Q_OBJECT

public:
    SendThread(QObject *parent = nullptr) : QThread(parent)
       {
       }

       void setData(const QByteArray &data)
       {
           m_data = data;
       }
protected:
    void run() override
    {
        QTcpSocket socket;
        socket.connectToHost("localhost", 8080);
        if (socket.waitForConnected())
        {
            socket.write(m_data);
            socket.waitForBytesWritten();
            // Log des données envoyées ici
        }
        else
        {
            // Log des erreurs de connexion ici
        }
    }

private:
    QByteArray m_data;
};

#endif // MAINWINDOW_H
