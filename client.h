#ifndef CLIENT_H
#define CLIENT_H

#include <message.h>

class client
{
public:
    client(std::string name, ObjectForm form, ObjectDesc desc);
    ObjectForm getForm();
    ObjectDesc getDesc();
    char getName();

private:
    ObjectForm form;
    ObjectDesc desc;
    char name[MAXNAMELEN];
};

#endif // CLIENT_H
