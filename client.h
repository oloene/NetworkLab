#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

private:
    //method examples for reading server data
    void handleMoveMsg();
    void handleLeaveMsg();
    void handleNewPlayerMsg();

//notifies the view that a change has been made
signals:
    void notifyObserver();

public slots:
};

#endif // CLIENT_H
