#include "setup.h"
#include "ui_setup.h"
#include "view.h"
#include <QDebug>
#include "view.h"
#include <QString>
#include "client.h"
#include "networkModule.h"
#include <qhostaddress.h>
#include "keyboardhandler.h"

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
    client *localClient = new client(nullptr, name, Cube, Human);

    QHostAddress serverAddr;
    serverAddr.setAddress(ip);
    networkModule *_network = new networkModule(nullptr, serverAddr, port);
    _network->setLocalClient(localClient);
    _network->join();
    keyboardHandler keyB;
    connect(&keyB, SIGNAL(moveSig(int)), _network, SLOT(eventAction(int)));
    //e.g. Socket *_socket = new Socket();
    // _socket->connect(IP, PORT);

    this->hide();
    View *view = new View();
    view->show();



}



// TODO: design change, implement signal fo on button clicked. this will signal to the main class
// that the setup is done and can be read, which will start everything sequencially as current impl
// ementation.
// emit setupDone(ip, port, name);
