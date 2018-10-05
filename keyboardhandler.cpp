#include "keyboardhandler.h"
#include <QKeyEvent>
#include <QDebug>

void keyboardHandler::keyPressEvent(QKeyEvent *event){
    // according to networkMOdule 0 is right,1 left, 2 up, 3 down
    int direction;
    if (event->key() == Qt::Key_Right){
        direction = 0;
    } else if (event->key() == Qt::Key_Left){
        direction = 1;
    } else if (event->key() == Qt::Key_Up){
        direction = 2;
    } else if (event->key() == Qt::Key_Down){
        direction = 3;
    }

    emit moveSig(direction);
    qDebug() << "little keypress maybe";
}
