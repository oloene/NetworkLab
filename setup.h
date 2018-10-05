#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include <QAbstractButton>
#include "message.h"

namespace Ui {
class Setup;
}

class Setup : public QDialog
{
    Q_OBJECT

public:
    explicit Setup(QWidget *parent = 0);
    ~Setup();

signals:
    //QString ip, int port, QString name
    void setupDone(QString ip, int port, QString name);

private slots:
    void newPlayerSlot(int id, char name[]);
    void newPosSlot(int id, Coordinate pos, Coordinate dir);
    void on_buttonBox_clicked();

private:
    Ui::Setup *ui;
};

#endif // SETUP_H
