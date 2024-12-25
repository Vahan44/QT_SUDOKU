#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // Կապում ենք "OK" կոճակը `accept()` ֆունկցիայի հետ
    connect(ui->buttonOk, &QPushButton::clicked, this, &LoginDialog::accept);

    // Կապում ենք "Cancel" կոճակը `reject()` ֆունկցիայի հետ
    connect(ui->buttonCancel, &QPushButton::clicked, this, &LoginDialog::reject);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getUserName() const
{
    // Վերադարձնում ենք օգտվողի անունը, որը մուտքագրված է lineEditUserName-ում
    return ui->lineEditUserName->text();
}
