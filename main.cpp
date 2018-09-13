#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <Myrect.h>

/*
c++ game network lab
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const int SCREEN_WIDTH=480;
    const int SCREEN_HEIGHT=480;

    //create a scene which holds all data for the view
    QGraphicsScene *scene = new QGraphicsScene();

    //create a QGraphicsRectItem to put into the scene
    Myrect *rect = new Myrect();
    rect->setRect(0,0, rect->getWidth(), rect->getHeight());
    rect->setBrush(Qt::red);

    //tell scene that you want to focus the rect object so it can be moved
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();
    //add item to scene
    scene->addItem(rect);

    //add view and set scene at a fixed size
    QGraphicsView *view = new QGraphicsView();
    view->setScene(scene);
    view->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    view->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    view->fitInView(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Qt::KeepAspectRatio);
    view->show();

    return a.exec();
}
