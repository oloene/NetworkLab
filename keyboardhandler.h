#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H
#include <QKeyEvent>

class keyboardHandler : public QObject
{

    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);

signals:
    void moveSig(int direction);
};

#endif // KEYBOARDHANDLER_H
