#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>

//Myrect is a type of QGraphicsRectItem
//displayed in the main window
class Myrect : public QGraphicsRectItem {
public:
    void keyPressEvent(QKeyEvent *event);
    int getWidth(){return this->RECT_WIDTH;}
    int getHeight(){return this->RECT_HEIGHT;}

private:
    //20 by 20 rectangle
    const int RECT_WIDTH = 20;
    const int RECT_HEIGHT = 20;
};

#endif // MYRECT_H
