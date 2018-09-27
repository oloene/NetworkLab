#include <myrect.h>
#include <QDebug>
#include <QKeyEvent>

//key_event for moving the rectangle
void Myrect::keyPressEvent(QKeyEvent *event){
    //window dimensions
    //hard coded, change?
    const int SCREEN_WIDTH=480;
    const int SCREEN_HEIGHT=480;

    const int RECT_WIDTH = Myrect::getWidth();
    const int RECT_HEIGHT = Myrect::getHeight();
    const int PLAYER_VELOCITY = 10;

    /*
     * QKeyEvent reacting to keyboard arrows,
     * ensuring rectangle stays within screen bounds
     */
    if(event->key() == Qt::Key_Left){
        if(this->pos().x()-PLAYER_VELOCITY < 0){
            qDebug() << "myrect.cpp OUTSIDE_LEFT OF SCREEN" << endl;
        } else {
            setPos(x()-PLAYER_VELOCITY, y());
        }
    }
    else if(event->key() == Qt::Key_Right){
        if(this->pos().x()+RECT_WIDTH+PLAYER_VELOCITY > SCREEN_WIDTH){
            qDebug() << "myrect.cpp OUTSIDE_RIGHT OF SCREEN" << endl;
        } else {
            setPos(x()+PLAYER_VELOCITY, y());
        }
    }
    else if(event->key() == Qt::Key_Down){
        if(this->pos().y()+RECT_HEIGHT+PLAYER_VELOCITY > SCREEN_HEIGHT){
            qDebug() << "myrect.cpp OUTSIDE_BOTTOM OF SCREEN" << endl;
        } else {
            setPos(x(), y()+PLAYER_VELOCITY);
        }
    }
    else if(event->key() == Qt::Key_Up){
        if(this->pos().y()-PLAYER_VELOCITY < 0){
            qDebug() << "myrect.cpp OUTSIDE_TOP OF SCREEN" << endl;
        } else {
            setPos(x(), y()-PLAYER_VELOCITY);
        }
    }
}


