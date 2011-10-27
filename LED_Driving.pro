#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T22:19:13
#
#-------------------------------------------------

QT       += core gui

TARGET = LED_Driving
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp
    
LIBS += -L. -lsum -lgpio
	
HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xea7fe867
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
