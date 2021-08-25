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
    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(result.toUtf8(), & error);
    if (error.error == QJsonParseError::NoError && json.isObject()) {
    }
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

