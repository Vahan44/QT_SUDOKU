#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        QString userName = loginDialog.getUserName();
        qDebug() << "User Name:" << userName; // Տպում ենք օգտվողի անունը

        MainWindow w;
        w.addUser(userName);
        w.show();

        return a.exec();
    }

    return 0;
}
