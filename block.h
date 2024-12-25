#ifndef BLOCK_H
#define BLOCK_H
#include <QLineEdit>
#include <QValidator>
#include <QtGui>
#include <QPalette>

class Block :public QWidget
{
    Q_OBJECT

public:
    Block(QWidget *parent=0);
    void setValue(int a);
    int getValue();
    void changeColor(const QColor &color);

private slots:
    void dataChange(const QString & data);
    void valueChange();

signals:
    void valueChanged();
    void confirmAnswers();


private:
    QLineEdit *nubEidt;
    int da;
    QPalette pal;
};

#endif // BLOCK_H
