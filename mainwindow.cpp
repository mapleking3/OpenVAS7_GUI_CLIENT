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
#include "omp.h"

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
    OmpSession *omp_session = new OmpSession(ui->edit_ip->text(), ui->edit_port->text().toUShort());

    if (!omp_session->authenticate(ui->edit_un->text(),ui->edit_pw->text()))
    {
        QMessageBox::information(this, "failed to authenticate", "connect to openvasmd authenticate failed");
        return;
    }

    InstanceDialog *inst = new InstanceDialog(this, omp_session);
    inst->show();
    QString title("OpenVAS Manager: ");
    title.append(ui->edit_ip->text());
    inst->setWindowTitle(title);
}

void MainWindow::on_cancel_clicked()
{
    QCoreApplication::quit();
}
