#include "block.h"

Block::Block(QWidget *parent)
    :QWidget(parent)
{
    nubEidt=new QLineEdit(this);
    nubEidt->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPixelSize(30);

    QPalette palette=this->palette();
    palette.setColor(QPalette ::Disabled,QPalette::Text,Qt::white);
    nubEidt->setPalette(palette);

    nubEidt->setFont(font);
    nubEidt->setMinimumSize(50,50);
    nubEidt->setMaximumSize(50,50);


    connect(nubEidt,SIGNAL(textChanged(QString)),this,SLOT(dataChange(QString)));
    connect(nubEidt,SIGNAL(textEdited(QString)),this,SLOT(valueChange()));
    nubEidt->setText("");
    da = -1;
}

void Block::valueChange()
{
    emit valueChanged();
}

void Block::changeColor(const QColor &color)
{
    QPalette pal;
    pal.setColor(QPalette::Text,color);
    nubEidt->setPalette(pal);
}

void Block::setValue(int a)
{
    if(a<1)
    {
        nubEidt->setText("");
        da= -1;
    }
    else
    {
        nubEidt->setText(QString::number(a));
        da=a;
    }
}

int Block::getValue()
{
    QString num;
    num = nubEidt->text();
    int nums = num.toInt();
    return nums;
}

void Block::dataChange(const QString &data)
{
    if(data.isEmpty())
    {
        da=-1;
    }
    else
    {
        da=data.toInt();
        emit confirmAnswers();
    }
}

