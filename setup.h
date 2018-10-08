#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include <QAbstractButton>
#include "message.h"
#include "client.h"
#include "view.h"
#include "networkModule.h"


namespace Ui {
class Setup;
}

class Setup : public QDialog
{
    Q_OBJECT

public:
    explicit Setup(QWidget *parent = nullptr);
    ~Setup();

signals:
    //QString ip, int port, QString name
    void setupDone();

private slots:
    void addClient(client *);
    void on_buttonBox_clicked();
    void newPlayer(uint id);
    void newPos(uint id, Coordinate pos, Coordinate dir);

private:
    View *view;
    Ui::Setup *ui;
    client *clients[40] = {nullptr}; //support for clientid up to 40
    bool isLocalPlayer = true;
    networkModule *_network;
};

#endif // SETUP_H
