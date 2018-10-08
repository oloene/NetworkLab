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
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";
    qDebug() << "in add client to scene in veiw";

//    client->setRect(client->getPosX() +100 , client->getPosY()+100, client->getWidth(), client->getHeight());
//    qDebug() << "setBrush";
//    client->setBrush(Qt::red);

//    if(this->isLocalPlayer){
//        qDebug() << "is local palyer";
//        client->setFlag(QGraphicsItem::ItemIsFocusable);
//        client->setFocus();
//        this->isLocalPlayer = false;
//    }
    client->setRect(client->getPosX() +100 , client->getPosY()+100, client->getWidth(), client->getHeight());

    client->setBrush(Qt::red);

    client->setFlag(QGraphicsItem::ItemIsFocusable);
    client->setFocus();
    qDebug() << "add client to scene";
    scene->clear();
    scene->addItem(client);
}
