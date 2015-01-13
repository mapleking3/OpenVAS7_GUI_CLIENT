#ifndef __PARAMS_H__
#define __PARAMS_H__

#include <QPair>
#include <QList>
#include <QString>

class Params;

class param
{
public:
    param() : child(NULL) {}
    QString name;
    QString value;
    QPair<QString,QString> prop;
    Params *child;
};

class Params
{
    public:
        Params() {}
        ~Params() {}

        void addParam(const QString &name, const QString &value, QPair<QString,QString> prop, Params *child)
        {
            param p;
            p.child = child;
            p.name = name;
            p.value = value;
            p.prop = prop;
            _params.insert(_params.end(),p);
        }

        void addParam(const QString &name, const QString &value, QPair<QString,QString> prop)
        {
            addParam(name, value, prop, NULL);
        }

        void addParam(const QString &name, const QString &value)
        {
            addParam(name, value, QPair<QString,QString>(), NULL);
        }

        void addParam(const QString &name, QPair<QString,QString> prop)
        {
            addParam(name, QString(), prop, NULL);
        }

        void addParam(const QString &name, Params *p)
        {
            addParam(name, QString(), QPair<QString,QString>(), p);
        }

    //private:
        QList<struct param> _params;
};

#endif ///< __PARAMS_H__
