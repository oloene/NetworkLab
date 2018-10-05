#include "setup.h"
#include "ui_setup.h"
#include "view.h"
#include <QDebug>
#include "view.h"
#include <QString>
#include "client.h"
#include "networkModule.h"
#include <qhostaddress.h>
#include "message.h"

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
    View *view = new View();
    connect(_network, SIGNAL(joinSig(client *)), this, SLOT(addClientToScene(client *)));
    connect(localClient, SIGNAL(moveSig(int)), _network, SLOT(eventAction(int)));
    connect(_network, SIGNAL(newPosSig(int, Coordinate, Coordinate)), this, SLOT(handleClientPos(int, Coordinate, Coordinate)));
    _network->setLocalClient(localClient);
    _network->join();


    this->hide();
    view->show();
}

void Setup::handleClientPos(int id, Coordinate pos, Coordinate dir){
    //client current = find(clients, );
    // lookup client by client id number, is same as in clients array
}

void Setup::addClient(client *client){
    clients[client->getClientId()] = client;
    view->addClientToScene(client);
}

// TODO: design change, implement signal fo on button clicked. this will signal to the main class
// that the setup is done and can be read, which will start everything sequencially as current impl
// ementation.
// emit setupDone(ip, port, name);
