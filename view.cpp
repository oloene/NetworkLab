#include "view.h"
#include <QDebug>
#include "client.h"

//main view
View::View(QGraphicsView *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setScene(scene);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //initScene();

}

//void View::initScene(){
//    client *client = new class client(Cube, Human);
//    client->setRect(client->getPosX() +100 , client->getPosY()+100, client->getWidth(), client->getHeight());
//    client->setBrush(Qt::red);
//    client->setFlag(QGraphicsItem::ItemIsFocusable);
//    client->setFocus();
//    scene->addItem(client);
//}
//_client emits a notifyObserver() SIGNAL
void View::has_changed(){
   qDebug() << "repainting the window... \n";
}

void View::addClientToScene(client *client){
    qDebug() << "in add client to scene in veiw";

    client->setRect(client->getPosX() , client->getPosY(), client->getWidth(), client->getHeight());
    //client->setRect(client->x(), client->y(), client->getWidth(), client->getHeight());
    qDebug() << "setBrush";
    client->setBrush(Qt::red);

    if(this->isLocalPlayer){
        qDebug() << "is local palyer";
        client->setFlag(QGraphicsItem::ItemIsFocusable);
        client->setFocus();
        this->isLocalPlayer = false;
    }
//    client->setRect(client->getPosX() +100 , client->getPosY()+100, client->getWidth(), client->getHeight());

//    client->setBrush(Qt::red);

//    client->setFlag(QGraphicsItem::ItemIsFocusable);
//    client->setFocus();
    qDebug() << "add client to scene";
    qDebug() << this->scene;
    //scene->clear();
    scene->addItem(client);
}
