#include "network.h"
#include "message.h"
//#include "sys/socket.h"
#include "qtcpsocket.h"
#include "client.h"
#include <QObject>

network::network(QObject *parent, QHostAddress ipAddr, int portNum) : QObject(parent)
{
    network::ip = ipAddr;
    network::port = portNum;
    network::socket = new QTcpSocket();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    //connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    // works connect(socket, SIGNAL(readyRead()), this, SLOT(handleMsg()));
    connectSocket();
}

void network::connectSocket(){
    socket->connectToHost(network::ip, network::port);
    if(socket->waitForConnected(network::timeout)){
        qDebug() << "Connected to server.";
    } else {
        qDebug() << socket->error();
    }
}

void network::send(char *msg){
    // use for debug socket->write((char *)&msg);

    try {
        socket->write(msg);
        //throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void network::close(){
    try {
        socket->close();
        throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }

}

void network::join(client *client){
    try {
        JoinMsg msg;
        msg.desc = client->getDesc();
        msg.form = client->getForm();
        strncpy(msg.name, client->getName(), sizeof(client->getName()) - 1);

        MsgHead header = {sizeof (msg),  client->getSeqNum(), client->getClientId(), MsgType::Join};
        msg.head = header;

        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar);
        qDebug() << "join Server";
        //throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void network::leave(client client){
    try {
        LeaveMsg msg;
        MsgHead header = {sizeof (msg),  client.getSeqNum(), client.getClientId(), MsgType::Leave};
        msg.head = header;

        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar);
        throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void network::eventAction(client *client){
    try {
        EventMsg msg;
        msg.type = Move;
        MsgHead header = {sizeof (msg),  client->getSeqNum(), client->getClientId(), MsgType::Event};
        msg.head = header;

        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar);
        throw socket->error();;
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void network::readData(){
    socket->bytesAvailable();
    qDebug() << "in read data";
    qDebug() << socket->readAll();

}

void network::readyRead(){
    qDebug() << "in read data";
    qDebug() << socket->readAll();
}

void network::handleMsg(){
    qDebug() << "what";
}
