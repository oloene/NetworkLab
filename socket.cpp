#include "socket.h"
#include "message.h"

Socket::Socket(QObject *parent) : QObject(parent)
{

}

//create a TCP socket and connect to the given server
void Socket::Connect() {

    JoinMsg joinMsg;
    joinMsg.desc = ObjectDesc::NonHuman;
    joinMsg.form = ObjectForm::Cube;
    joinMsg.name[0] = 'o';

    MsgHead header = { sizeof(joinMsg), 0, 0, MsgType::Join };
    joinMsg.head = header;

    socket = new QTcpSocket(this);
    //bcast: 130.240.42.63
    //inet: 130.240.40.12
    socket->connectToHost("130.240.40.7", 49152);

    if(socket->waitForConnected(4000)){
        qDebug() << "Connected!";

        //send
        socket->write((char *)&joinMsg);

        qDebug() << "wrote to server";

        socket->close();

    }
    else {
        qDebug() << "Connection timed out";
        qDebug() << socket->error();
    }

}
