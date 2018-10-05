#ifndef CLIENT_H
#define CLIENT_H

#include <message.h>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class client : public QObject, public QGraphicsRectItem
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
    void keyPressEvent(QKeyEvent *event);
    int getWidth();
    int getHeight();

private:
    unsigned int id;
    ObjectForm form;
    ObjectDesc desc;
    char name[MAXNAMELEN];
    unsigned int seqNum = 0;
    Coordinate pos;
    Coordinate dir;
    const int RECT_WIDTH = 5;
    const int RECT_HEIGHT = 5;

signals:
    void notifyObserver();
    void moveSig(int direction);

public slots:
    void handleMsg();
};

#endif // CLIENT_H
