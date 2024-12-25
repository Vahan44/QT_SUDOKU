QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku
TEMPLATE = app


SOURCES += main.cpp\
    logindialog.cpp \
        mainwindow.cpp \
    block.cpp \
    sudokuData.cpp \
    gline.cpp

HEADERS  += mainwindow.h \
    block.h \
    logindialog.h \
    sudokuData.h \
    gline.h

FORMS    += mainwindow.ui \
         LoginDialog.ui
