#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <client.h>


#define SCREEN_HEIGHT 406
#define SCREEN_WIDTH 406

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
    void addClientToScene(client *client, bool isLocalPlayer);

};

#endif // VIEW_H
