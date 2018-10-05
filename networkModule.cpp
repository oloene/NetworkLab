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

void networkModule::setLocalClient(client *localClient){
    networkModule::localClient = localClient;
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
        localClient->incSeqNum();
        //qDebug() << "msg contents" << msg;
        //qDebug() << "size of msg:" << sizeof (msg);
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

void networkModule::join(){
    try {
        JoinMsg msg;
        MsgHead head = {sizeof (msg), 0, 0, MsgType::Join};
        msg.head = head;
        msg.desc = localClient->getDesc();
        msg.form = localClient->getForm();
        strncpy(msg.name, localClient->getName(), sizeof(localClient->getName()) - 1);
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

// Leave msg only contains a head which is correct according to spec.
void networkModule::leave(){
    try {
        LeaveMsg msg;
        MsgHead head = {sizeof (msg),  localClient->getSeqNum(), localClient->getClientId(), MsgType::Leave};

        int msgSize = sizeof(msg); // check size of the entire message, inorder to be able to send all bytes.
        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar, msgSize);
        //throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void networkModule::eventAction(int direction){
    try {
        MoveEvent moveEventMsg;
        MsgHead head = {sizeof (moveEventMsg),  localClient->getSeqNum(), localClient->getClientId(), MsgType::Event};
        EventMsg msg;
        msg.head = head;
        msg.type = Move;

        moveEventMsg.event = msg;
        moveEventMsg.dir = localClient->getDir();
        Coordinate newPos;
        switch (direction) {
            // 0 will be RIGHT
            case 0:
                qDebug() << "eventAction got right";
                newPos = localClient->getPos();
                newPos.x++;
                break;
            // 1 will be LEFT
            case 1:
                qDebug() << "eventAction got left";
                newPos = localClient->getPos();
                newPos.x--;
                break;
            // 2 will be UP
            case 2:
                qDebug() << "eventAction got up";
                newPos = localClient->getPos();
                newPos.y--;
                break;
            // 3 will be DOWN
            case 3:
                qDebug() << "eventAction got down";
                newPos = localClient->getPos();
                newPos.y++;
                break;

        }
        moveEventMsg.pos = newPos;

        int msgSize = sizeof(moveEventMsg); // check size of the entire message, inorder to be able to send all bytes.
        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar, msgSize);
        //throw socket->error();;
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
    int availNumBytes = socket->bytesAvailable();
    char recvBuffer[availNumBytes];
    socket->read(recvBuffer, availNumBytes);

    MsgHead *msg = (MsgHead *)recvBuffer;
    qDebug() << "id:" << msg->id;
    qDebug() << "len:" << msg->length;
    qDebug() << "size of posPTR" << posPtr;
    qDebug()  << "size of buffer" << sizeof(recvBuffer);
    while(posPtr < sizeof(recvBuffer)){
        qDebug() << "ptr:" << posPtr;
        ChangeMsg *changeMsg;
        JoinMsg *joinMsg;
        NewPlayerMsg *newPlayerMsg;
        NewPlayerPositionMsg *newPlayerPosMsg;
        PlayerLeaveMsg *playerLeaveMsg;

        switch(msg->type){
            case MsgType::Change:
                qDebug() << "changeType";
                changeMsg = (ChangeMsg *)&recvBuffer[posPtr];
                qDebug() << "message head:" << changeMsg->head.id;
                qDebug() << "message len:" << changeMsg->head.length;
                switch (changeMsg->type) {
                    case NewPlayer:
                        qDebug() << "new player";
                        newPlayerMsg = (NewPlayerMsg *)&recvBuffer[posPtr];
                        // signal that makes main create a new client with this client id, name etc.
                        // emit newPlayerSig(newPlayerMsg->head.id, newPlayerMsg->desc, newPlayerMsg->form, newPlayerMsg->name);
                        break;
                    case NewPlayerPosition:
                        qDebug() << "new position";
                        newPlayerPosMsg = (NewPlayerPositionMsg *)&recvBuffer[posPtr];
                        // main or "model" will get signal that somone got updated pos. searches list of clients and updates accordinly
                        // emit newPlayerPosSig(newPlayerPosMsg->head.id, newPlayerPosMsg->pos, newPlayerPosMsg->dir);
                        break;
                    case PlayerLeave:
                        qDebug() << "player left!";
                        playerLeaveMsg = (PlayerLeaveMsg *)&recvBuffer[posPtr];
                        // main or "model" gets signal that someone left the game, search the client list for correct id and pop.
                        // emit playerLeaveSig(playerLeaveMsg->head.id);
                        break;
                }
                posPtr += changeMsg->head.length;
                //char *tmpMsg[512];
                //strncpy(tmpMsg, recvBuffer[posPtr], recvBuffer[posPtr]);
                break;
            case MsgType::Join:
                qDebug() << "joinType";
                joinMsg = (JoinMsg *)recvBuffer;
                localClient->setClientId(joinMsg->head.id);
                qDebug() << "id (2):" << joinMsg->head.id;
                posPtr += joinMsg->head.length;
                break;
            default:
                break;
        }
        qDebug() << msg->length;
        //posPtr += msg->length;
    }

}
