#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include <QAbstractButton>
#include "message.h"
#include "client.h"
#include "view.h"

namespace Ui {
class Setup;
}

class Setup : public QDialog
{
    Q_OBJECT

public:
    explicit Setup(QWidget *parent = 0);
    ~Setup();

signals:
    //QString ip, int port, QString name
    void setupDone();

private slots:
    void handleClientPos(int id, Coordinate pos, Coordinate dir);
    void addClient(client *);
    void on_buttonBox_clicked();
    void newPlayerSlot(int id, char name[]);
    void newposSlot(int id, Coordinate pos, Coordinate dir);

private:
    View *view;
    Ui::Setup *ui;
    client *clients[100]; //support for clientid up to a hundred
};

#endif // SETUP_H
