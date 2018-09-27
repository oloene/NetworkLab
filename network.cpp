#include "network.h"
#include "message.h"
//#include "sys/socket.h"
#include "qtcpsocket.h"
#include "client.h"


network::network(QHostAddress ipAddr, int portNum)
{
    network::ip = ipAddr;
    network::port = portNum;
    connect();
    join();
}

// thought was to be able to check if connection is succesfull, return true, continue with program etc.
bool network::connect(){
    network::socket = new QTcpSocket();
    socket->connectToHost(network::ip, network::port);
    if(socket->waitForConnected(network::timeout)){
        qDebug() << "Connected to server.";
    } else {
        qDebug() << socket->error();
    }
}

//TODO: check old style cast
void network::send(char *msg){
    // use for debug socket->write((char *)&msg);

    try {
        socket->write(msg);
        throw socket->error();
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

void network::join(client client){
    try {
        JoinMsg msg;
        msg.desc = client::desc;
        msg.form = client.getForm();
        msg.name = client::name;

        MsgHead header = {sizeof (msg), 0, 0, MsgType::Join};
        msg.head = header;

        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar);
        throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void network::leave(client client){
    try {
        LeaveMsg msg;
        MsgHead header = {sizeof (msg), 0, 0, MsgType::Leave};
        msg.head = header;

        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar);
        throw socket->error();
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}

void network::event(client client){
    try {
        EventMsg msg;
        MsgHead header = {sizeof (msg), 0, 0, MsgType::Event};
        msg.head = header;

        char *msgChar = reinterpret_cast<char*>(&msg);
        send(msgChar);
        throw socket->error();;
    } catch (QTcpSocket::SocketError e) {
        qDebug() << e;
    }
}
