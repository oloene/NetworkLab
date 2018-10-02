#include "setup.h"
#include "ui_setup.h"
#include "view.h"
#include <QDebug>
#include "view.h"
#include <QString>
#include "client.h"
#include "networkModule.h"
#include <qhostaddress.h>

Setup::Setup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setup)
{
    ui->setupUi(this);
}

Setup::~Setup()
{
    delete ui;
}

//OK button clicked
void Setup::on_buttonBox_clicked()
{
    //grab text info from setup window
    QString ip = ui->IP_EDIT->text();
    int port = ui->PORT_EDIT->text().toInt();
    QString name = ui->NAME_EDIT->text();
    qDebug() << ip << port << name;

    client *_client = new client(nullptr, name, Cube, Human);

    QHostAddress serverAddr;
    serverAddr.setAddress(ip);
    networkModule *_network = new networkModule(nullptr, serverAddr, port);
    _network->join(_client);
    //e.g. Socket *_socket = new Socket();
    // _socket->connect(IP, PORT);

    this->hide();
    View *view = new View();
    view->show();
}
