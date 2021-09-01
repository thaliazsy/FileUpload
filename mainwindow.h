#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QMainWindow>
#include <QFile>

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
    void finished(QNetworkReply* reply);    //upload finish

    void on_selectBtn_clicked();            //call file selection dialog

    void on_uploadFileBtn_clicked();        //upload file
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal); //upload in progress

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager m_manager;
    QStringList fileNames;
    QString dirPath;
    QFile *myFile;
    int fileCount;
    int uploadedDICOMCount;
    int progressValue;
};
#endif // MAINWINDOW_H
