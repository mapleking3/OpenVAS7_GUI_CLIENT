#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QMessageBox>
#include <QCoreApplication>
#include <QtNetwork/QSslSocket>
#include <QIODevice>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslCertificate>
#include <QFile>

#include "instance.h"
#include "genxml.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_clicked()
{
    QSslSocket *ssl_socket = new QSslSocket(this);
    if (NULL == ssl_socket)
    {
        qDebug("create QSslSocket Error!\n");
        exit(0);
    }
    QFile *file = new QFile("/home/retton/cacert.pem");
    if (NULL == file)
    {
        qDebug("create file error!\n");
        exit(0);
    }
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    ssl_socket->addCaCertificate(QSslCertificate(file));
    ssl_socket->connectToHostEncrypted(ui->edit_ip->text(), ui->edit_port->text().toUShort(),
                                       QIODevice::ReadWrite,QAbstractSocket::IPv4Protocol);
    if (!ssl_socket->waitForEncrypted()) {
        qDebug() << ssl_socket->errorString();
        exit(0);
    }

    Params p;
    p.addParam("username", "admin");
    p.addParam("password", "zxsoft");

    Params credentials;
    credentials.addParam("credentials", &p);

    ssl_socket->write(GenXml(GenXml::EAUTHENTICATE,credentials).GetXml());
    if (ssl_socket->waitForReadyRead())
    {
        qDebug("%s\n",ssl_socket->readAll().data());
    }

    InstanceDialog *inst = new InstanceDialog(this, ssl_socket);
    inst->show();
    QString title("OpenVAS Manager: ");
    title.append(ui->edit_ip->text());
    inst->setWindowTitle(title);
}

void MainWindow::on_cancel_clicked()
{
    QCoreApplication::quit();
}
