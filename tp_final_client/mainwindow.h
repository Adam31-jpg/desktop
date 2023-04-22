#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QDate>


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

#endif // MAINWINDOW_H
