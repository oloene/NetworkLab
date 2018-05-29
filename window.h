#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPushButton;
class QProgressBar;
class QSlider;

class Window : public QWidget {
//used to create a costum-made slot
Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

//the costum-made slot methods
private slots:
    void slotButtonClicked(bool checked);

private:
    QPushButton *m_button;
    QProgressBar *progressBar;
    QSlider *slider;
};

#endif // WINDOW_H
