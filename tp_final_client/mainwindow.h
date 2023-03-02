#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListView>
#include <QMainWindow>
#include <QStringListModel>
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
    void on_lineEdit_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    void initConnection();
    void receiveData();
};

#endif // MAINWINDOW_H
