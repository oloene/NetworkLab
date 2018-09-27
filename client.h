#ifndef CLIENT_H
#define CLIENT_H

#include <message.h>

class client
{
public:
    client(std::string name, ObjectForm form, ObjectDesc desc);
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
};

#endif // CLIENT_H
