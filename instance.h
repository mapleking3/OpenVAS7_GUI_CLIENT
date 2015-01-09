#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include <QMainWindow>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSslSocket;

namespace Ui {
    class Instance;
}

class InstanceDialog : public QMainWindow
{
    Q_OBJECT
    public:
        InstanceDialog(QWidget *parent = 0, QSslSocket *ssl_socke = NULL);
        ~InstanceDialog();


private slots:
        void get_tasks();
        void get_targets();

private:
        Ui::Instance *_inst_ui;
        QSslSocket *_ssl_socket;
};

#endif ///< __INSTANCE_H__
