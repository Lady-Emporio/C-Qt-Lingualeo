#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(slotButton()));









}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotButton()
{
    QObject* obj = sender();
    ui->label->setText(obj->objectName());
}
