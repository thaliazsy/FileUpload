#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDir>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&this->m_manager, &QNetworkAccessManager::finished, this, &MainWindow::finished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::finished(QNetworkReply * reply)
{
    QString url = reply -> url().toString();

    QString type = url.split('/').last();
    ui -> textEdit -> append(type);

    QString result = QString(reply -> readAll());
    ui->textEdit_result -> append(result);
    ui->selectBtn->setEnabled(true);
}

void MainWindow::on_selectBtn_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec()){
        fileNames = dialog.selectedFiles();
    }
    if (fileNames.length() > 0) {
        ui -> uploadFileBtn -> setEnabled(true);

        fileCount = fileNames.length();

        //START: display file names
        QString files = "";
        foreach(QString f, fileNames) {
            files += f + "; ";
        }
        ui -> filesEdit -> setText(files);
        //END: display file names

        //START: get destination folder path
        QFileInfo f(fileNames[0]);
        dirPath = f.path();
        ui->textEdit->append(dirPath+"\n");
        //END: get destination folder path

        foreach(QString f, fileNames){
            QFileInfo file (f);
            ui->textEdit->append(file.completeBaseName() + "\t" + file.suffix()+"\n");
        }

        //START: create ImagingStudy

        //END: create ImagingStudy
    }
    ui -> progressBar -> reset();

}

void MainWindow::on_uploadFileBtn_clicked()
{
    //ftp://user4@203.64.84.150:20221/DocumentReference

    foreach(QString f, fileNames){

        QFileInfo file (f);
        QUrl url(ui->ftpEdit->text() + "/" + file.fileName());
        url.setUserName("user4");    // Set login
        url.setPassword("4efb@plkj"); // Set ????????????
        url.setPort(20221);


        myFile = new QFile(f);
        // Start upload
        QNetworkReply *reply = m_manager.put(QNetworkRequest(url), myFile);
        // And connect to the progress upload signal
        connect(reply, &QNetworkReply::uploadProgress, this, &MainWindow::uploadProgress);
    }
}

void MainWindow::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    // Display the progress of the upload
    //ui->progressBar->setValue(100 * bytesSent/bytesTotal);
}
