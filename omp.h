#ifndef OMP_H
#define OMP_H

#include <QString>
#include <QtNetwork/QSslSocket>
#include <QIODevice>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslCertificate>
#include <QFile>

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

struct cmd_authenticate {
    QString username;
    QString password;
};

struct cmd_authenticate_resp {
    QString status;
    QString status_text;
    QString role;
    QString timezone;
};

struct cmd_create_agent {
    QString installer;
    QString signature;
    QString name;
    QString comment;
    QString copy;
    QString howto_install;
    QString howto_use;
};

struct cmd_create_agent_resp {
    QString status;
    QString status_text;
    QString id;
};

struct cmd_get_tasks {
    QString task_id;
    QString filter;
    QString filter_id;
    QString trash;
    QString details;
    QString rcfile;
    QString apply_overrides;
};

struct cmd_get_tasks_resp {
    QString status;
    QString status_text;
    QString apply_overides;
    //QList
};

class OmpSession
{
public:
    OmpSession(const QString &ip = DEF_OMP_SRV_IP, const int port = DEF_OMP_SRV_PORT,
               const QString &cafile= DEF_OMP_SRV_CAFILE);
    ~OmpSession();

    int get_tasks();
    bool authenticate(const QString &username, const QString &password);

private:
    QSslSocket *_ssl_socket;
};

#endif // OMP_H
