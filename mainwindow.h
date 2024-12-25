#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "block.h"
#include "ui_mainwindow.h"
#include "sudokuData.h"
#include "gline.h"
#include <QMainWindow>
#include <QFrame>
#include <QPushButton>
#include <QLayout>
#include <QGridLayout>
#include <cstring>
#include <QMenu>
#include <QMessageBox>
#include <iostream>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void addUser(const QString &username);
    ~MainWindow();

private slots:
    void initializeDatabase();

    void easyInitialize();
    void mediumInitialize();
    void hardInitialize();
    void veryhardInitialize();
    void blocksClear();
    void checkBlocks();
    void checkAnswers();
    void blocksReset();

private:
    void createMenu();
    void createBlocks();
    void drawLine();

private:
    Ui::MainWindow *ui;

    enum{Max=9};

    Block *blocks[Max][Max];

    QFrame *frame;

    QPushButton *easyButton;
    QPushButton *mediumButton;
    QPushButton *hardButton;
    QPushButton *veryhardButton;
    QPushButton *confirmButton;
    QPushButton *clearButton;
    QPushButton *resetButton;
    QPushButton *quitButton;
    QPushButton *aboutButton;
    QPushButton *helpButton;


    bool flag, cflag, rflag, eflag, sflag;
    int nums[9];
};

#endif // MAINWINDOW_H
