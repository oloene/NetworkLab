#ifndef CLIENT_H
#define CLIENT_H

#include <message.h>
#include <QObject>

class client : public QObject
{
    Q_OBJECT

public:
    explicit client(QObject *parent = nullptr, std::string name = "NoName", ObjectForm form = Cube, ObjectDesc desc = Human);
    ObjectForm getForm();
    ObjectDesc getDesc();
    char* getName();
    void incSeqNum();
    unsigned int getSeqNum();
    void setPosX(int newPosX);
    int getPosX();
    void setPosY(int newPosY);
    int getPosY();
    unsigned int getClientId();

private:
    unsigned int id;
    ObjectForm form;
    ObjectDesc desc;
    char name[MAXNAMELEN];
    unsigned int seqNum = 0;
    int x;
    int y;

signals:
    void notifyObserver();

public slots:
    void handleMsg();
};

#endif // CLIENT_H
