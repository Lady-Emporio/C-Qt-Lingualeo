#include "widget.h"
#include "ui_widget.h"
//#include <QtSql>
#include <vector>
#include <algorithm>
#include <QDebug>
const int SUMBUT=4;//количество кнопок.

void pushInMyListID(std::vector<int> &MyVec,int const &MaxInt){
    for(;;){
        if(MyVec.size()==SUMBUT){break;}
        int nextId=qrand() % MaxInt;
        if(!std::count(MyVec.begin(), MyVec.end(), nextId)){
            MyVec.push_back(nextId);
        }

    };
}
void Widget::startNewWorld(){
    ui->pushButton_1->setStyleSheet("background-color: rgb(245, 242, 221);");
    ui->pushButton_2->setStyleSheet("background-color: rgb(245, 242, 221);");
    ui->pushButton_3->setStyleSheet("background-color: rgb(245, 242, 221);");
    ui->pushButton_4->setStyleSheet("background-color: rgb(245, 242, 221);");
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName("lingualeo.db");
//    if (!db.open()){
//           ui->label->setText("Not !db.open()");
//    }
//    else{
    int MAXROWDB=0;
    //QSqlQuery query;
    query=db.exec( QString( "SELECT MAX(id) from MainTable" ) );
    //query=db.exec( QString( "SELECT eng, ru FROM MainTable where id=6" ) );
    query.first();
    MAXROWDB=query.value(0).toInt();
    //ui->label->setText(QString(std::to_string(MAXROWDB).c_str())  );  //max row in db
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); //инициализация каким-то числом генератора. Вообще не знаю, как эта страка работает, но она инициализирует seed уникальным числом.

    std::vector<int> ListIntId;
    pushInMyListID(ListIntId,MAXROWDB);
    QString World[4][4]; //ru,eng,audio, image;
    int tryWorld=qrand() % SUMBUT;
    for(int i=0;i!=SUMBUT;i++){
        query=db.exec( QString( "SELECT eng, ru,audio,image FROM MainTable where id=?;" ) );
        query.addBindValue(ListIntId[i]);
        query.exec();
        query.first();
        World[i][0]=query.value(0).toString();
        World[i][1]=query.value(1).toString();
        World[i][2]=query.value(2).toString();
        World[i][3]=query.value(3).toString();
        if(i==tryWorld){
            ChooseWord[0]=query.value(0).toString();
            ChooseWord[1]=query.value(1).toString();
        }
    }
    ui->label->setText(ChooseWord[1]);
    ui->pushButton_1->setText(World[0][0]);
    ui->pushButton_2->setText(World[1][0]);
    ui->pushButton_3->setText(World[2][0]);
    ui->pushButton_4->setText(World[3][0]);





}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    go_next=false;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lingualeo.db");
    if (!db.open()){
           ui->label->setText("Not !db.open()");
    }
    else{
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(slotButton()));
    startNewWorld();
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("lingualeo.db");
//    if (!db.open()){
//           ui->label->setText("Not !db.open()");
//    }
//    else{
//    int MAXROWDB=0;
//    QSqlQuery query;
//    query=db.exec( QString( "SELECT MAX(id) from MainTable" ) );
//    //query=db.exec( QString( "SELECT eng, ru FROM MainTable where id=6" ) );
//    query.first();
//    MAXROWDB=query.value(0).toInt();
//    //ui->label->setText(QString(std::to_string(MAXROWDB).c_str())  );  //max row in db
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); //инициализация каким-то числом генератора. Вообще не знаю, как эта страка работает, но она инициализирует seed уникальным числом.

//    std::vector<int> ListIntId;
//    pushInMyListID(ListIntId,MAXROWDB);
//    QString World[4][4]; //ru,eng,audio, image;
//    int tryWorld=qrand() % SUMBUT;
//    for(int i=0;i!=SUMBUT;i++){
//        query=db.exec( QString( "SELECT eng, ru,audio,image FROM MainTable where id=?;" ) );
//        query.addBindValue(ListIntId[i]);
//        query.exec();
//        query.first();
//        World[i][0]=query.value(0).toString();
//        World[i][1]=query.value(1).toString();
//        World[i][2]=query.value(2).toString();
//        World[i][3]=query.value(3).toString();
//        if(i==tryWorld){
//            ChooseWord[0]=query.value(0).toString();
//            ChooseWord[1]=query.value(1).toString();
//        }
//    }
//    ui->label->setText(ChooseWord[1]);
//    ui->pushButton_1->setText(World[0][0]);
//    ui->pushButton_2->setText(World[1][0]);
//    ui->pushButton_3->setText(World[2][0]);
//    ui->pushButton_4->setText(World[3][0]);


//    };//else bd run
     };//else bd run
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotButton()
{
    QObject* obj = sender();
    //ui->label->setText(obj->objectName());
    QPushButton *buttom=findChild<QPushButton*>(obj->objectName());
    //qDebug()<<ChooseWord[0]<<" "<<buttom->text();
    if(buttom->text()==ChooseWord[0]){
        if (!go_next){
            buttom->setStyleSheet("background-color: green");
            go_next=true;
        }
        else{
            go_next=false;
            startNewWorld();
        }
    }
    else{
        buttom->setStyleSheet("background-color: red");
    }
}
