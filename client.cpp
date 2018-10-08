#include "client.h"
#include <bits/stdc++.h>
#include <message.h>
#include <QDebug>
#include <QKeyEvent>
#include "networkModule.h"


client::client(QObject *parent, ObjectForm form, ObjectDesc desc)
{
    //strcpy(client::name, name.c_str()); // implement length check on input, should not be longer than 32 (or maybe 31) chars.
    client::form = form;
    client::desc = desc;
    //strncpy(client::name, "", 31);

}

ObjectForm client::getForm(){
    return client::form;
}

ObjectDesc client::getDesc(){
    return client::desc;
}

char* client::getName(){
    return client::name;
}

void client::incSeqNum(){
    client::seqNum++;
}

unsigned int client::getSeqNum(){
    return client::seqNum;
}

void client::setPosX(int newPosX){
    client::pos.x = newPosX;
    client::setX((100-newPosX)*5);
}

int client::getPosX(){
    return client::pos.x;
}

void client::setPosY(int newPosY){
    client::pos.y = newPosY;
    client::setY((100-newPosY)*5);

}

int client::getPosY(){
    return client::pos.y;
}


//void client::setDirX(int newDirX){
//    client::dir.x = newDirX;
//}

//int client::getDirX(){
//    return client::dir.x;
//}

//void client::setDirY(int newDirY){
//    client::dir.y = newDirY;
//}

//int client::getDirY(){
//    return client::dir.y;
//}

Coordinate client::getDir(){
    return client::dir;
}

Coordinate client::getPos(){
    return client::pos;
}

unsigned int client::getClientId(){
    return client::id;
}

void client::setClientId(unsigned int id){
    client::id = id;
}

int client::getWidth(){
    return this->RECT_WIDTH;
}

int client::getHeight(){
    return  this->RECT_HEIGHT;
}

void client::keyPressEvent(QKeyEvent *event){
    // according to networkMOdule 0 is right,1 left, 2 up, 3 down
    //QGraphicsItem::keyPressEvent(event);
    int direction;
    if (event->key() == Qt::Key_Right){
        direction = 0;
    } else if (event->key() == Qt::Key_Left){
        direction = 1;
    } else if (event->key() == Qt::Key_Up){
        direction = 2;
    } else if (event->key() == Qt::Key_Down){
        direction = 3;
    }
    emit moveSig(direction);
    qDebug() << "little keypress maybe";
}

