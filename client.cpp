#include "client.h"
#include <bits/stdc++.h>
#include <message.h>
#include <QDebug>

client::client(QObject *parent, QString name, ObjectForm form, ObjectDesc desc) : QObject(parent)
{
    //strcpy(client::name, name.c_str()); // implement length check on input, should not be longer than 32 (or maybe 31) chars.
    client::form = form;
    client::desc = desc;
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
}

int client::getPosX(){
    return client::pos.x;
}

void client::setPosY(int newPosY){
    client::pos.y = newPosY;
}

int client::getPosY(){
    return client::pos.y;
}


void client::setDirX(int newDirX){
    client::dir.x = newDirX;
}

int client::getDirX(){
    return client::dir.x;
}

void client::setDirY(int newDirY){
    client::dir.y = newDirY;
}

int client::getDirY(){
    return client::dir.y;
}

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

void client::handleMsg(){

}

