#include "setup.h"
#include "ui_setup.h"
#include "view.h"
#include <QDebug>
#include "view.h"
#include <QString>
#include "client.h"
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
    //client *localClient = new client(nullptr, Cube, Human);

    QHostAddress serverAddr;
    serverAddr.setAddress(ip);
    _network = new networkModule(nullptr, serverAddr, port);
    _network->join(name);

    view = new View();
    connect(_network, SIGNAL(joinSig(uint)), this, SLOT(setLocalClientId(uint))); // special case for localplayer ?
    connect(_network, SIGNAL(newPosSig(uint, Coordinate, Coordinate)), this, SLOT(newPos(uint, Coordinate, Coordinate)));
    connect(_network, SIGNAL(newPlayerSig(uint)), this, SLOT(newPlayer(uint)));

    //_network->setLocalClient(localClient);
    //_network->join();

    this->hide();
    view->show();
}

void Setup::setLocalClientId(uint id){
    localPlayerId = id;
}

void Setup::newPos(uint id, Coordinate pos, Coordinate dir){
    // lookup client by client id number, is same as in clients array
    qDebug() << "newPos in setup: x: " << pos.x << "y:" << pos.y ;
    clients[id]->setPosX(pos.x);
    clients[id]->setPosY(pos.y);
//    clients[id]->setDirX(dir.x);
//    clients[id]->setDirY(dir.y);
}

void Setup::addClient(client *client){
    qDebug() << "add Client in setup";
    uint tempId = client->getClientId();
    if(clients[tempId] == nullptr){ // checks so that we dont double assign a player due to the servers nature of sending double messages
        clients[tempId] = client;    // take id of client and assign it to the corresponding place in array.
        if(isLocalPlayer && (tempId == localPlayerId)){
            _network->setLocalClient(clients[tempId]);
            connect(clients[tempId], SIGNAL(moveSig(int)), _network, SLOT(eventAction(int)));   // keyboard signal generates event to send
            view->addClientToScene(clients[client->getClientId()], isLocalPlayer);
            isLocalPlayer = false;
        }else{
            view->addClientToScene(clients[client->getClientId()], false);             // add the new client to the GUI scene
        }
        qDebug() << "add client to scene";
    }

}

void Setup::newPlayer(uint id){
    qDebug() << "newPlayer in setup";
    client *networkPlayer = new client(nullptr, Cube, Human);
    networkPlayer->setClientId(id);
    qDebug() << "networkplayer id" <<  networkPlayer->getClientId();
    addClient(networkPlayer);
}


// TODO: design change, implement signal fo on button clicked. this will signal to the main class
// that the setup is done and can be read, which will start everything sequencially as current impl
// ementation.
// emit setupDone(ip, port, name);
