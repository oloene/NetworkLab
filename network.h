#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <QTcpSocket>
#include <QHostAddress>
#include <message.h>

// forward declaration to not include class.
class client;

class network
{
public:
    network(QHostAddress ip, int port);

private:
    QHostAddress ip;
    int port;
    int timeout = 4000;     // wait 4 sec for connection
    QTcpSocket *socket;

    bool connect();
    void send(char *msg);
    void close();
    void join(client client);
    void leave(client client);
    void event(client client);
};

#endif // NETWORK_H
