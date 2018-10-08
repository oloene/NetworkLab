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
    //delete ui;
}

//OK button clicked
void Setup::on_buttonBox_clicked()
{
    //grab text info from setup window
    QString ip = ui->IP_EDIT->text();
    int port = ui->PORT_EDIT->text().toInt();
    QString name = ui->NAME_EDIT->text();
    qDebug() << ip << port << name;
    client *localClient = new client(Cube, Human);

    QHostAddress serverAddr;
    serverAddr.setAddress(ip);
    networkModule *_network = new networkModule(nullptr, serverAddr, port);
    View *view = new View();
    //connect(_network, SIGNAL(joinSig(client *)), this, SLOT(addClient(client *))); // special case for localplayer ?
    //connect(localClient, SIGNAL(moveSig(int)), _network, SLOT(eventAction(int)));   // keyboard signal generates event to send
    connect(_network, SIGNAL(newPosSig(uint, Coordinate, Coordinate)), this, SLOT(newPos(uint, Coordinate, Coordinate)));
    connect(_network, SIGNAL(newPlayerSig(uint)), this, SLOT(newPlayer(uint)));

    _network->setLocalClient(localClient);
    _network->join();

    this->hide();
    view->show();
}

void Setup::newPos(uint id, Coordinate pos, Coordinate dir){
    //client current = find(clients, );
    // lookup client by client id number, is same as in clients array
    qDebug() << "newPos in setup";
    clients[id]->setPosX(pos.x);
    clients[id]->setPosY(pos.y);
//    clients[id]->setDirX(dir.x);
//    clients[id]->setDirY(dir.y);
}

void Setup::addClient(client *client){
    qDebug() << "add Client in setup";
    uint tempId = client->getClientId();
    clients[tempId] = client;    // take id of client and assign it to the corresponding place in array.
    qDebug() << "add client to scene";
    view->addClientToScene(clients[client->getClientId()]);             // add the new client to the GUI scene
}

void Setup::newPlayer(uint id){
    qDebug() << "newPlayer in setup";
    client *networkPlayer = new client(Cube, Human);
    networkPlayer->setClientId(id);
    qDebug() << "networkplayer id" <<  networkPlayer->getClientId();
    addClient(networkPlayer);
}


// TODO: design change, implement signal fo on button clicked. this will signal to the main class
// that the setup is done and can be read, which will start everything sequencially as current impl
// ementation.
// emit setupDone(ip, port, name);
