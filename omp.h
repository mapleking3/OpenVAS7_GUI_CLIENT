#ifndef OMP_H
#define OMP_H

#include <QString>
#include <QtNetwork/QSslSocket>
#include <QIODevice>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslCertificate>
#include <QFile>
#include <QXmlSimpleReader>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#include <QMessageBox>

#include "genxml.h"

#define DEF_OMP_SRV_IP "127.0.0.1"
#define DEF_OMP_SRV_PORT 9390
#define DEF_OMP_SRV_CAFILE "Z:\\OpenVAS7_GUI_CLIENT\\cacert.pem"

typedef enum {
    ESTATUS_200     = 200,
    ESTATUS_201     = 201,
    ESTATUS_202     = 202,
    ESTATUS_400     = 400,
    ESTATUS_401     = 401,
    ESTATUS_403     = 403,
    ESTATUS_404     = 404,
    ESTATUS_409     = 409,
    ESTATUS_500     = 500,
    ESTATUS_503     = 503
} EOMP_RESP_STATUS;

class OmpException
{
public:
    OmpException(const int nErrCode)
    {
        _err_code = nErrCode;
    }
    OmpException(const OmpException&  e)
    {
        _err_code = e._err_code;
    }
    virtual ~OmpException();

    int GetErrorCode() const { return _err_code; }	

    //static const char* GetErrorCodeAsString(const int nErrCode);
	
private:
    int    _err_code;
};

class OmpSession
{
public:
    OmpSession(const QString &ip = DEF_OMP_SRV_IP, const int port = DEF_OMP_SRV_PORT,
               const QString &cafile= DEF_OMP_SRV_CAFILE);
    ~OmpSession();

    QDomDocument *get_tasks(const QDomDocument &doc);
    QDomDocument *create_task(const QDomDocument &doc);
    QDomDocument *delete_task(const QDomDocument &doc);
    bool authenticate(const QString &username, const QString &password);

private:
    QDomDocument *omp(const QDomDocument &doc);

    QSslSocket *_ssl_socket;
};

#endif // OMP_H
