# TYPE TO BUILD, CAN BE APPLICATION, A LIBRARY or A SIMPLE SUBDIRECTORY
TEMPLATE = app

#NAME OF THE APPLICATION
TARGET = my_first_QT_app

#WHAT TYPE OF QT LIBRARIES
#CORE AND GUI HERE
QT = core gui

#CHECK VERSION CONTROL
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# ADD SOURCE FILES TO QT APPLICATION
# Headers and sources files can be added manually with
# HEADERS += first_file.h second_file.h
# SOURCES += first_file.cpp second_file.cpp
SOURCES += \
    main.cpp \
    window.cpp

HEADERS += \
    window.h
