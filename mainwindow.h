#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void finished(QNetworkReply* reply);

    void on_selectBtn_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager m_manager;
    QStringList fileNames;
    QString dirPath;
    int fileCount;
    int uploadedDICOMCount;
    int progressValue;
};
#endif // MAINWINDOW_H
