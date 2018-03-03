#ifndef WIDGET_H
#define WIDGET_H
#include <QtSql>
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void startNewWorld();
private slots:
    void slotButton();
public:
    Ui::Widget *ui;
    QString ChooseWord[2];
    bool go_next;
    QSqlDatabase db;
    QSqlQuery query;
};




#endif // WIDGET_H
