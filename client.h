#ifndef CLIENT_H
#define CLIENT_H

#include <message.h>
#include <QObject>
#include <QKeyEvent>

class client : public QObject
{
    Q_OBJECT

public:
    explicit client(QObject *parent = nullptr, QString name = "NoName", ObjectForm form = Cube, ObjectDesc desc = Human);
    ObjectForm getForm();
    ObjectDesc getDesc();
    char* getName();
    void incSeqNum();
    unsigned int getSeqNum();
    void setPosX(int newPosX);
    int getPosX();
    void setPosY(int newPosY);
    int getPosY();
    void setDirX(int newDirX);
    int getDirX();
    void setDirY(int newDirY);
    int getDirY();
    Coordinate getDir();
    Coordinate getPos();
    unsigned int getClientId();
    void setClientId(unsigned int id);

private:
    unsigned int id;
    ObjectForm form;
    ObjectDesc desc;
    char name[MAXNAMELEN];
    unsigned int seqNum = 0;
    Coordinate pos;
    Coordinate dir;

signals:
    void notifyObserver();

public slots:
    void handleMsg();
};

#endif // CLIENT_H
