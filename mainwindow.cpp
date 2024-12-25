#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    flag = false;
    eflag = true;
    cflag = true ;
    rflag = true ;
    sflag = true;

    createMenu();

    frame=new QFrame(this);
    initializeDatabase();
    createBlocks();
    drawLine();

    this->setFixedSize(600,500);
    frame->move(15,15);
    this->setWindowTitle("Sudoku");
}



void MainWindow::initializeDatabase() {
    // Ստեղծում ենք տվյալների բազայի միացում
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sudoku.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database!" << db.lastError().text();
        return;
    }

    QSqlQuery query;

    // Ստեղծում ենք Users աղյուսակը
    QString createUsersTableQuery =
        "CREATE TABLE IF NOT EXISTS Users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL UNIQUE, "
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    if (!query.exec(createUsersTableQuery)) {
        qDebug() << "Error creating Users table:" << query.lastError().text();
    } else {
        qDebug() << "Users table created successfully!";
    }
}


void MainWindow::addUser(const QString &username) {
    QSqlQuery query;
    query.prepare("INSERT INTO Users (username) VALUES (:username)");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error adding user:" << query.lastError().text();

    }
    else {
          qDebug() << "User added successfully!";
        }

}




void MainWindow::easyInitialize()
{

    blocksReset();

    int nums = 0;
    nums = (int)(6.0*rand()/(RAND_MAX+1.0));

	easyRandom(nums);

    for(int i=0 ; i<Max ; i++)
    {
        for(int j=0 ; j<Max ; j++)
        {
            if(sudokuData::num[i][j]!=0)
            {
                blocks[i][j]->setValue(sudokuData::num[i][j]);
                blocks[i][j]->setEnabled(false);
                blocks[i][j]->setStyleSheet("background-color:rgba(0,0,0,0)");
            }
            else
            {
                connect(blocks[i][j],SIGNAL(valueChanged()),this,SLOT(checkBlocks()));
                connect(blocks[i][j],SIGNAL(confirmAnswers()),this,SLOT(checkAnswers()));
            }
        }
    }

    flag=true;
}

void MainWindow::mediumInitialize()
{

    blocksReset();

    int nums = 0;
    nums = (int)(6.0*rand()/(RAND_MAX+1.0));

    mediumRandom(nums);

    for(int i=0 ; i<Max ; i++)
    {
        for(int j=0 ; j<Max ; j++)
        {
            if(sudokuData::num[i][j]!=0)
            {
                blocks[i][j]->setValue(sudokuData::num[i][j]);
                blocks[i][j]->setEnabled(false);
                blocks[i][j]->setStyleSheet("background-color:rgba(0,0,0,0)");
            }
            else
            {
                connect(blocks[i][j],SIGNAL(valueChanged()),this,SLOT(checkBlocks()));
                connect(blocks[i][j],SIGNAL(confirmAnswers()),this,SLOT(checkAnswers()));
            }
        }
    }

    flag=true;
}

void MainWindow::hardInitialize()
{
    blocksReset();

    int nums = 0;
    nums = (int)(6.0*rand()/(RAND_MAX+1.0));

    hardRandom(nums);

    for(int i=0 ; i<Max ; i++)
    {
        for(int j=0 ; j<Max ; j++)
        {
            if(sudokuData::num[i][j]!=0)
            {
                blocks[i][j]->setValue(sudokuData::num[i][j]);
                blocks[i][j]->setEnabled(false);
                blocks[i][j]->setStyleSheet("background-color:rgba(0,0,0,0)");
            }
            else
            {
                connect(blocks[i][j],SIGNAL(valueChanged()),this,SLOT(checkBlocks()));
                connect(blocks[i][j],SIGNAL(confirmAnswers()),this,SLOT(checkAnswers()));
            }
        }
    }

    flag=true;
}

void MainWindow::veryhardInitialize()
{
    blocksReset();

    int nums = 0;
    nums = (int)(6.0*rand()/(RAND_MAX+1.0));

    veryhardRandom(nums);

    for(int i=0 ; i<Max ; i++)
    {
        for(int j=0 ; j<Max ; j++)
        {
            if(sudokuData::num[i][j]!=0)
            {
                blocks[i][j]->setValue(sudokuData::num[i][j]);
                blocks[i][j]->setEnabled(false);
                blocks[i][j]->setStyleSheet("background-color:rgba(0,0,0,0)");
            }
            else
            {
                connect(blocks[i][j],SIGNAL(valueChanged()),this,SLOT(checkBlocks()));
                connect(blocks[i][j],SIGNAL(confirmAnswers()),this,SLOT(checkAnswers()));
            }
        }
    }

    flag = true;
}

void MainWindow::createBlocks()
{
    for(int i=0;i<Max;i++)
    {
        for(int j=0;j<Max;j++)
        {
            blocks[i][j]=new Block(frame);
            blocks[i][j]->move(j*50,i*50);
        }
    }
    int w=(50)*9+1;
    frame->setMinimumSize(w,w);    
}

void MainWindow::drawLine()
{
    GLine *line_H[4];
    QColor color;
    QRgb rgb=qRgb(0,0,0);
    color.setRgb(rgb);
    for(int i=0;i<4;i++)
    {
        line_H[i]=new GLine(frame);
        line_H[i]->setPen(3,color);
        line_H[i]->draw(1,frame->height());
        if(i>0)
             line_H[i]->move(blocks[0][i*3+1]->pos().x()+blocks[0][i*3+1]->width()-2,0);
        else
            line_H[i]->move(0,0);
    }

    GLine *line_V[4];
    for(int i=0;i<4;i++)
    {
        line_V[i]=new GLine(frame);
        line_V[i]->setPen(3,color);
        line_V[i]->draw(0,frame->width());
        if(i>0)
            line_V[i]->move(0,blocks[i*3-1][0]->pos().y()+blocks[i*3-1][0]->height()+ui->menuBar->height()-11);
        else
            line_V[i]->move(0,0);
    }
}

void MainWindow::blocksReset()
{
    for(int i=0 ; i<Max ; i++)
    {
        for(int j=0 ; j<Max ; j++)
        {
            blocks[i][j]->setValue(0);
            blocks[i][j]->setEnabled(true);
            sudokuData::num[i][j]=0;
            blocks[i][j]->changeColor(Qt::white);
            disconnect(blocks[i][j], 0, 0, 0) ;
        }
    }

    flag=false;
}

void MainWindow::blocksClear()
{
    for(int i=0 ; i<Max ; i++)
    {
        for(int j=0 ; j<Max ; j++)
        {
            if (sudokuData::num[i][j] == 0)
            {
                blocks[i][j]->setValue(0);
            }
            blocks[i][j]->changeColor(Qt::white);
        }
    }
}

void MainWindow::checkBlocks()
{
    cflag = true;
    rflag = true;
    sflag = true;
    if (flag == true)
    {
        for(int i=0 ; i<Max ; i++)
        {
            for(int j=0 ; j<Max ; j++)
            {
                blocks[i][j]->changeColor(Qt::white);
            }
        }

        for (int i=0 ; i<Max ; i++)
        {
            for(int j=0;j<Max;j++)
            {
                nums[j]= blocks[j][i]->getValue();
            }

            for (int m=0 ; m<Max ; m++)
            {
                for (int n=m+1 ; n<Max ; n++)
                {
                    if(nums[m] == nums[n])
                    {
                        blocks[m][i]->changeColor(Qt::red);
                        blocks[n][i]->changeColor(Qt::red);
                        cflag = false;
                    }
                }
            }
        }

        for (int i=0 ; i<Max ; i++)
        {
            for(int j=0;j<Max;j++)
            {
                nums[j]= blocks[i][j]->getValue();
            }

            for (int m=0 ; m<Max ; m++)
            {
                for (int n=m+1 ; n<Max ; n++)
                {
                    if(nums[m] == nums[n])
                    {
                        blocks[i][m]->changeColor(Qt::red);
                        blocks[i][n]->changeColor(Qt::red);
                        rflag = false;
                    }
                }
            }
        }

        for(int row=0 ; row<Max ; row=row+3)
        {
            for(int col=0 ; col<Max ; col=col+3)
            {
                int s=0;
                for (int i=row ; i<row+3 ; i++)
                {
                    for(int j=col ; j<col+3 ; j++)
                    {
                        nums[s]= blocks[i][j]->getValue();
                        s++;
                    }
                }

                for (int i=0 ; i<Max ; i++)
                {
                    for (int j=i+1 ; j<Max ; j++)
                    {
                        if(nums[i] == nums[j])
                        {
                            if (i<3)
                            {
                                blocks[row][i+col]->changeColor(Qt::red);
                                if (j<3)
                                {
                                    blocks[row][j+col]->changeColor(Qt::red);
                                }
                                if (2<j && j<6)
                                {
                                    blocks[row+1][j+col-3]->changeColor(Qt::red);
                                }
                                if (5<j && j<9)
                                {
                                    blocks[row+2][j+col-6]->changeColor(Qt::red);
                                }
                            }
                            if (2<i && i<6)
                            {
                                blocks[row+1][i+col-3]->changeColor(Qt::red);
                                if (2<j && j<6)
                                {
                                    blocks[row+1][j+col-3]->changeColor(Qt::red);
                                }
                                if (5<j && j<9)
                                {
                                    blocks[row+2][j+col-6]->changeColor(Qt::red);
                                }
                            }
                            if (5<i && i<9)
                            {
                                blocks[row+2][i+col-6]->changeColor(Qt::red);
                                blocks[row+2][j+col-6]->changeColor(Qt::red);
                            }
                        sflag = false;
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::checkAnswers()
{
    for(int i=0 ; i<Max ; i++)
    {
        for(int j=0 ; j<Max ;j++)
        {
            if(blocks[i][j]->getValue() > 0)
            {
                eflag = true;
            }
            else
            {
                eflag = false;
                break;
            }
        }
        if (eflag == false)
        {
            break;
        }
    }

    if (flag == true && cflag == true && rflag == true && sflag == true && eflag == true)
    {
        QMessageBox::information(this, "Congratulations", "Your solve this puzzle", QMessageBox::Ok );

        for(int i=0 ; i<Max ; i++)
        {
            for(int j=0 ; j<Max ;j++)
            {
                blocks[i][j]->setEnabled(false);
            }
        }
    }
}

void  MainWindow::createMenu()
{
    easyButton = new QPushButton(tr("Easy"),this);
    easyButton->setGeometry(485,40,100,30);
    easyButton->show();
    connect(easyButton,SIGNAL(clicked()),this,SLOT(easyInitialize()));

    mediumButton = new QPushButton(tr("Medium"),this);
    mediumButton->setGeometry(485,80,100,30);
    mediumButton->show();
    connect(mediumButton,SIGNAL(clicked()),this,SLOT(mediumInitialize()));

    hardButton = new QPushButton(tr("Hard"),this);
    hardButton->setGeometry(485,120,100,30);
    hardButton->show();
    connect(hardButton,SIGNAL(clicked()),this,SLOT(hardInitialize()));

    veryhardButton = new QPushButton(tr("Very Hard"),this);
    veryhardButton->setGeometry(485,160,100,30);
    veryhardButton->show();
    connect(veryhardButton,SIGNAL(clicked()),this,SLOT(veryhardInitialize()));

    clearButton = new QPushButton(tr("Clear"),this);
    clearButton->setGeometry(485,330,100,30);
    clearButton->show();
    connect(clearButton,SIGNAL(clicked()),this,SLOT(blocksClear()));

    resetButton = new QPushButton(tr("Reset"),this);
    resetButton->setGeometry(485,370,100,30);
    resetButton->show();
    connect(resetButton,SIGNAL(clicked()),this,SLOT(blocksReset()));

    quitButton = new QPushButton(tr("Quit"),this);
    quitButton->setGeometry(485,410,100,30);
    quitButton->show();
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
