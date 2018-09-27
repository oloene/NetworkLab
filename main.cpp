#include "client.h"
#include "view.h"
#include <QApplication>
#include <QPushButton>
#include<QObject>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //create an empty view
    View *_view = new View();

    //TODO: create a socket connected to the server
    //e.g. Socket *_socket = new Socket();
    // _socket->connect(IP, PORT);

    //TODO: create a player thread for key inputs, sending moveMsg's to server
    //e.g. Player *_player = new Player(_id, _name);
    // _player->start();

    //TODO: create a client thread to read data from server and update view
    client *_client = new client(nullptr, "bert", Cube, Human);
    // _client->start();

    //_view observing _client through SIGNAL and SLOT
    QObject::connect(_client, SIGNAL(notifyObserver()), _view, SLOT(has_changed()) );
    //TODO: emit signal inside the client thread
    //TODO: implement methods inside client thread to handle server messages
    emit _client->notifyObserver();

    //display view
    _view->show();
    return a.exec();
}
