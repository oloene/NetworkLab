#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <QTcpSocket>
#include <QHostAddress>
#include <message.h>

// forward declaration to not include class.
class client;

class network : public QObject
{

Q_OBJECT

signals:
    void recvMsg();

private slots:
    void handleMsg();
    void readData();
    void readyRead();

public:
    network(QObject *parent = nullptr, QHostAddress ip = QHostAddress::AnyIPv4, int port = 00000);
    void join(client *client);
    void eventAction(client *client);

private:
    QHostAddress ip;
    int port;
    int timeout = 4000;     // wait 4 sec for connection
    QTcpSocket *socket;

    void connectSocket();
    void send(char *msg);
    void close();
    void leave(client client);
    //void readData();
};

#endif // NETWORK_H
