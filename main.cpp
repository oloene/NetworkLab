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
    stp->show();

    return a.exec();
}
