#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>

#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 200

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QGraphicsView * parent = nullptr);

private:
    QGraphicsScene *scene;

signals:

public slots:
    //view observing the client
    void has_changed();

};

#endif // VIEW_H
