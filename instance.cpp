#include "instance.h"
#include "ui_instance.h"
#include "genxml.h"
#include "omp.h"

#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QSslSocket>
#include <QTreeWidgetItem>
#include <QXmlSimpleReader>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>

InstanceDialog::InstanceDialog(QWidget *parent, OmpSession *omp_session)
    : QMainWindow(parent),_inst_ui(new Ui::Instance())
{
    _inst_ui->setupUi(this);

    _omp_session = omp_session;

    connect(_inst_ui->tasks_action, SIGNAL(triggered()), this, SLOT(get_tasks()));
}

InstanceDialog::~InstanceDialog()
{
    delete _inst_ui;
}

void InstanceDialog::get_targets()
{
}

void InstanceDialog::get_tasks()
{
#if 0
    _omp_session->get_tasks();
    _ssl_socket->write(GenXml(GenXml::EGET_TASKS).GetXml());
    if (_ssl_socket->waitForReadyRead())
    {
        QDomDocument doc;
        QString errorMsg;
        int errorLine = 0, errorCol = 0;
        doc.setContent(_ssl_socket->readAll(),false, &errorMsg, &errorLine,&errorCol);
        if (doc.isNull())
        {
            qDebug("failed to parse xml!\n");
            exit(-2);
        }

        QDomElement root = doc.documentElement();
        if (root.tagName() != QString("get_tasks_response"))
        {
            qDebug("root name:%s !\n", root.tagName().toStdString().c_str());
            return;
        }

        if (!root.hasAttribute(QString("status")) || !root.hasAttribute(QString("status_text")))
        {
            qDebug("status not exist!\n");
            return;
        }

        if (root.attributeNode("status").value() != "200"
                || root.attributeNode("status_text").value() != "OK")
        {
            qDebug("status not ok!\n");
            return;
        }

        QDomNodeList node_list(root.childNodes());

        for (int index = 0; index < node_list.count(); ++index)
        {
            QDomNode node(node_list.item(index));
            QDomElement elem(node.toElement());

            if (elem.tagName() == "task")
            {
                QDomNodeList node_list(elem.childNodes());
                QTreeWidgetItem *item = new QTreeWidgetItem(_inst_ui->tasks_tree_widget);
                for (int index = 0; index < node_list.count(); ++index)
                {
                    QDomNode node(node_list.item(index));
                    QDomElement elem(node.toElement());

                    if (elem.tagName() == "name")
                    {
                        item->setText(0, elem.text());
                    }
                    else if (elem.tagName() == "status")
                    {
                        item->setText(1, elem.text());
                    }
                }
            }
        }
    }
#endif
}
