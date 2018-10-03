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
    client::x = newPosX;
}

int client::getPosX(){
    return client::y;
}

void client::setPosY(int newPosY){
    client::y = newPosY;
}

int client::getPosY(){
    return client::y;
}

unsigned int client::getClientId(){
    return client::id;
}

void client::setClientId(unsigned int id){
    client::id = id;
}

void client::handleMsg(){

}

