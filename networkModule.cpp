#include "networkModule.h"
#include "message.h"
//#include "sys/socket.h"
#include "qtcpsocket.h"
#include "client.h"
#include <QObject>
#include <QTextCodec>
#include <byteswap.h>

networkModule::networkModule(QObject *parent, QHostAddress ipAddr, int portNum) : QObject(parent)
{
    networkModule::ip = ipAddr;
    networkModule::port = portNum;
    networkModule::socket = new QTcpSocket();

    //connect(socket, SIGNAL(readyRead()), this, SLOT(readyReady()));
    //connect(socket, &QIODevice::readyRead, this, &networkModule::readyRead);
    connect(socket, SIGNAL(readyRead()), this, SLOT(handleMsg()));
    connectSocket();
    //readyRead();
}

void networkModule::connectSocket(){
    socket->connectToHost(networkModule::ip, networkModule::port);
    if(socket->waitForConnected(networkModule::timeout)){
        qDebug() << "Connected to server.";
    } else {
        qDebug() << socket->error();
    }
}

void networkModule::send(char *msg, int msgSize){
    // use for debug socket->write((char *)&msg);

    try {
        qDebug() << "msg contents" << msg;
        qDebug() << "size of msg:" << sizeof (msg);
        socket->write(msg, msgSize);
        //throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void networkModule::close(){
    try {
        socket->close();
        throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }

}

void networkModule::join(client *client){
    try {
        JoinMsg msg;
        MsgHead head = {sizeof (msg), 0, 0, MsgType::Join};
        msg.head = head;
        msg.desc = client->getDesc();
        msg.form = client->getForm();
        strncpy(msg.name, client->getName(), sizeof(client->getName()) - 1);
        //char *msgChar = reinterpret_cast<char*>(&msg);
        int msgSize = sizeof(msg); // check size of the entire message, inorder to be able to send all bytes.
        char *msgBuffer = (char *)&msg;
        send(msgBuffer, msgSize);

        qDebug() << "join Server";
        //throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void networkModule::leave(client client){
    try {
        LeaveMsg msg;
        MsgHead head = {sizeof (msg),  client.getSeqNum(), client.getClientId(), MsgType::Leave};

        int msgSize = sizeof(msg); // check size of the entire message, inorder to be able to send all bytes.
        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar, msgSize);
        //throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void networkModule::eventAction(client *client){
    try {
        EventMsg msg;
        msg.type = Move;
        MsgHead head = {sizeof (msg),  client->getSeqNum(), client->getClientId(), MsgType::Event};
        msg.head = head;

        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar, 8);
        throw socket->error();;
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}
void networkModule::readyRead(){

}

void networkModule::handleMsg(){
    qDebug() << "what";
    qDebug() << socket->bytesAvailable();
    //char *recvBuffer;
    //recvBuffer.append(socket->readAll());

    unsigned long posPtr = 0;
    //char *recvBuffer = (char *)socket->readAll().data();

    char recvBuffer[512];
    socket->read(recvBuffer, 512);

    MsgHead *msg = (MsgHead *)recvBuffer;
    qDebug() << "id:" << msg->id;
    qDebug() << "len:" << msg->length;
    qDebug() << "size of posPTR" << posPtr;
    qDebug()  << "size of buffer" << sizeof(recvBuffer);
    while(posPtr < sizeof(recvBuffer)){
        qDebug() << "ptr:" << posPtr;
        ChangeMsg *changeMsg;
        JoinMsg *joinMsg;
        EventMsg *eventMsg;
        LeaveMsg *leaveMsg;

        switch(msg->type){
            case MsgType::Event:
                qDebug() << "eventType";
                break;
            case MsgType::Change:
                qDebug() << "changeType";
                changeMsg = (ChangeMsg *)recvBuffer[posPtr];
                qDebug() << "message head:" << changeMsg->head.id;
                qDebug() << "message len:" << changeMsg->head.length;
                //char *tmpMsg[512];
                //strncpy(tmpMsg, recvBuffer[posPtr], recvBuffer[posPtr]);
                break;
            case MsgType::Join:
                qDebug() << "joinType";
                joinMsg = (JoinMsg *)recvBuffer;
                client->setClientId() = joinMsg->head.id;
                TODO: "implement client into this function or other design.";
                qDebug() << "id (2):" << joinMsg->head.id;

                break;
            case MsgType::Leave:
                qDebug() << "leaveType";
            break;
            default:
                break;
        }
        qDebug() << msg->length;
        posPtr += msg->length;
    }

}

