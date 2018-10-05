#include "client.h"
#include "view.h"
#include "networkModule.h"
#include <QApplication>
#include <QPushButton>
#include <QObject>
#include <setup.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //setup window
    Setup *stp = new Setup();
    //QObject::connect(stp, SIGNAL(setupDone()),SLOT(gameStart));
    stp->show();

    return a.exec();
}


// TODO: make main "model and controller", in this case, create a contianer of some kind that holds
// client objects that represent players. so that these can be added to the view canvas.
