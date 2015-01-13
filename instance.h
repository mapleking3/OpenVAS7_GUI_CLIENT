#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include <QMainWindow>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSslSocket;
class OmpSession;

namespace Ui {
    class Instance;
}

class InstanceDialog : public QMainWindow
{
    Q_OBJECT
    public:
        InstanceDialog(QWidget *parent = 0, OmpSession *omp_session = NULL);
        ~InstanceDialog();


private slots:
        void get_tasks();
        void get_targets();

private:
        Ui::Instance *_inst_ui;
        OmpSession *_omp_session;
};

#endif ///< __INSTANCE_H__
