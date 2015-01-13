#include "omp.h"
#include "genxml.h"

#include <QXmlSimpleReader>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#include <QMessageBox>

OmpSession::OmpSession(const QString &ip, const int port, const QString &cafile)
{
    _ssl_socket = new QSslSocket();
    if (NULL == _ssl_socket)
    {
        qDebug("create QSslSocket Error!\n");
        exit(0);
    }
    QFile *file = new QFile(cafile);
    if (NULL == file)
    {
        qDebug("create file error!\n");
        exit(0);
    }
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    _ssl_socket->addCaCertificate(QSslCertificate(file));
    _ssl_socket->connectToHostEncrypted(ip, quint16(port), QIODevice::ReadWrite,QAbstractSocket::IPv4Protocol);
    if (!_ssl_socket->waitForEncrypted()) {
        qDebug() << _ssl_socket->errorString();
        exit(0);
    }

    delete file;
}

OmpSession::~OmpSession()
{
    delete _ssl_socket;
}

bool OmpSession::authenticate(const QString &username, const QString &password)
{

    Params p;
    p.addParam("username", username);
    p.addParam("password", password);

    Params credentials;
    credentials.addParam("credentials", &p);

    QString auth_string(GenXml(GenXml::EAUTHENTICATE,credentials).GetXml());

    qDebug("auth string:%s\n", auth_string.toStdString().c_str());

    _ssl_socket->write(GenXml(GenXml::EAUTHENTICATE,credentials).GetXml().toStdString().c_str());
    if (_ssl_socket->waitForReadyRead())
    {
        QDomDocument doc;
        QString errorMsg;
        int errorLine = 0, errorCol = 0;
        doc.setContent(_ssl_socket->readAll(),false, &errorMsg, &errorLine,&errorCol);
        if (doc.isNull())
        {
            qDebug("failed to parse xml!\n");
            return false;
        }

        QDomElement root = doc.documentElement();
        if (root.tagName() != "authenticate_response")
        {
            qDebug("root name:%s !\n", root.tagName().toStdString().c_str());
            return false;
        }

        if (!root.hasAttribute(QString("status")) || !root.hasAttribute(QString("status_text")))
        {
            qDebug("status not exist!\n");
            return false;
        }

        if (root.attributeNode("status").value() != "200"
                || root.attributeNode("status_text").value() != "OK")
        {
            qDebug("%s\n",doc.toString().toStdString().c_str());
            qDebug("status not ok!\n");
            return false;
        }
    }
    return true;
}
