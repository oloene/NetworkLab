#include "client.h"
#include <bits/stdc++.h>
#include <message.h>

client::client(std::string name, ObjectForm form, ObjectDesc desc)
{
    strcpy(client::name, name.c_str()); // implement length check on input, should not be longer than 32 (or maybe 31) chars.
    client::form = form;
    client::desc = desc;
}

ObjectForm client::getForm(){
    return client::form;
}

ObjectDesc client::getDesc(){
    return client::desc;
}

char* client::getName(){
    return client::name;
}
