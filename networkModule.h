#ifndef NETWORKMODULE_H
#define NETWORKMODULE_H
#include <string>
#include <QTcpSocket>
#include <QHostAddress>
#include <message.h>

// forward declaration to not include class.
class client;

class networkModule : public QObject
{

Q_OBJECT

signals:
    void joinSig(client *client);
    void newPosSig(uint id, Coordinate pos, Coordinate dir);
    void newPlayerSig(uint id);
    void playerLeaveSig(uint id);

private slots:
    void handleMsg();
    void readyRead();
    void eventAction(int direction);

public:
    networkModule(QObject *parent = nullptr, QHostAddress ip = QHostAddress::AnyIPv4, int port = 00000);
    void join(QString name);
    void setLocalClient(client *localClient);

private:
    QHostAddress ip;
    int port;
    int timeout = 4000;     // wait 4 sec for connection
    QTcpSocket *socket;
    client *localClient;

    void connectSocket();
    void send(char *msg, int msgSize);
    void close();
    void leave();
    //void readData();
};

#endif // NETWORKMODULE_H
