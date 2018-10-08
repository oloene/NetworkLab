#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <client.h>


#define SCREEN_HEIGHT 1008
#define SCREEN_WIDTH 1008

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QGraphicsView * parent = nullptr);

private:
    QGraphicsScene *scene;
    bool isLocalPlayer = true;
    //void initScene();

signals:

public slots:
    //view observing the client
    void has_changed();
    void addClientToScene(client *client);

};

#endif // VIEW_H
