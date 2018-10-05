#include "view.h"
#include <QDebug>


//main view
View::View(QGraphicsView *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setScene(scene);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene->setSceneRect(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

//_client emits a notifyObserver() SIGNAL
void View::has_changed(){
   qDebug() << "repainting the window... \n";
}

void View::addClientToScene(client *client){
    client->setRect(client->getPosX(), client->getPosY(), client->getWidth(), client->getHeight());
    client->setBrush(Qt::red);
    if(isLocalPlayer){
        client->setFlag(QGraphicsItem::ItemIsFocusable);
        client->setFocus();
        isLocalPlayer = false;
    }

    scene->addItem(client);
}
