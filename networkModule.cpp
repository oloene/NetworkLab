#include "networkModule.h"
#include "message.h"
//#include "sys/socket.h"
#include "qtcpsocket.h"
#include "client.h"
#include <QObject>
#include <QTextCodec>

networkModule::networkModule(QObject *parent, QHostAddress ipAddr, int portNum) : QObject(parent)
{
    networkModule::ip = ipAddr;
    networkModule::port = portNum;
    networkModule::socket = new QTcpSocket();

    //connect(socket, SIGNAL(readyRead()), this, SLOT(readyReady()));
    //connect(socket, &QIODevice::readyRead, this, &networkModule::readyRead);
    connect(socket, SIGNAL(readyRead()), this, SLOT(handleMsg()));
    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_4_0);
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
        //msg = {head, client->getDesc(), client->getForm(), client->getName()};
        //msg = {head, ObjectDesc::Human, ObjectForm::Cube, };
        msg.head = head;
        msg.desc = client->getDesc();
        msg.form = client->getForm();
        strncpy(msg.name, client->getName(), sizeof(client->getName()) - 1);

        //char *msgChar = reinterpret_cast<char*>(&msg);
        int msgSize = sizeof(msg);
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

        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar, 8);
        throw socket->error();
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
        //socket->bytesAvailable();
        qDebug() << "in read data";
        QByteArray recvBuffer = socket->readAll();
        QString dataString(recvBuffer);
        qDebug() << dataString;

        //qDebug() << socket->readAll();
}

void networkModule::handleMsg(){
    qDebug() << "what";

    in.startTransaction();
    //QString msg;
    //in >> msg;
//    if (!in.commitTransaction()){
//        return;
//    }
    //qDebug() << msg;
    qDebug() << socket->bytesAvailable();
    /*if(socket->bytesAvailable()<150){
        return;
    }*/

    //char recvBuffer[512];
    //QByteArray qtBuffer = socket->readAll();
    //recvBuffer = (char *)&qtBuffer.data();
    char *recvBuffer = (char *)socket->readAll().data();


//    QTextCodec *codec = QTextCodec::codecForName("ASCII");
//    QTextDecoder *decoder = codec->makeDecoder();

//    QString string;
//    string += decoder->toUnicode(recvBuffer);
//    qDebug() << string;
//    delete decoder;


    MsgHead* msg = (MsgHead *)recvBuffer;
    //QString dataString(recvBuffer);
    qDebug() << msg;
    qDebug() << msg->type;
    if(msg->type == MsgType::Join){
        qDebug() << "player"<< msg->id << "joined";
    }

}
