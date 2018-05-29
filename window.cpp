#include "window.h"

#include <QPushButton>
#include <QApplication>
#include <QProgressBar>
#include <QSlider>

Window::Window(QWidget *parent) : QWidget(parent) {
    // Set size of the window
    setFixedSize(300, 300);

    // Create and position the button
    //add event to release signal
    m_button = new QPushButton("", this);
    m_button->setGeometry(215, 265, 80, 30);
    m_button->setCheckable(true);

    //create a progressbar
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setGeometry(10, 10, 225, 30);

    //create a slider
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0,100);
    slider->setValue(0);
    slider->setGeometry(10, 40, 180, 30);

    //connect the progressbar and the slider to eachother
    connect(slider, SIGNAL (valueChanged(int)), progressBar, SLOT (setValue(int)) );

    //connect a signal to a slot
    //i.e. kind of have the button object send a
    //signal to the application object instance to quit
    connect(m_button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)) );
}

//costum-made SLOT which will react to a signal from the button object
void Window::slotButtonClicked(bool checked) {
    QPalette pal = m_button->palette();
    if (checked) {
        m_button->setText("Checked!");
        pal.setColor(QPalette::Button, QColor(Qt::green));
    } else {
        m_button->setText("Unchecked!");
        pal.setColor(QPalette::Button, QColor(Qt::red));
    }
    m_button->setAutoFillBackground(true);
    m_button->setPalette(pal);
}
