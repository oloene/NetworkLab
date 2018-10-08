#ifndef CLIENT_H
#define CLIENT_H

#include <message.h>
#include <QGraphicsRectItem>
#include <QKeyEvent>
//#include <QObject>

class client : public QGraphicsRectItem
{

public:
    explicit client(ObjectForm form = Cube, ObjectDesc desc = Human);
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
    void keyPressEvent(QKeyEvent *event);
    int getWidth();
    int getHeight();

private:
    unsigned int id = 0;
    ObjectForm form;
    ObjectDesc desc;
    char name[MAXNAMELEN] = "amazons";
    unsigned int seqNum = 0;
    Coordinate pos = {
        0, //init pos x
        0,  //init pos y
    };
    const int RECT_WIDTH = 5;
    const int RECT_HEIGHT = 5;

//signals:
//    void notifyObserver();
//    void moveSig(int direction);

//public slots:
//    void handleMsg();
};

#endif // CLIENT_H
