#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QWidget>
#include <map.h>
#include <QRegExp>
static Create_map cat_map;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QList<QPushButton *> allbuttons = this->findChildren<QPushButton *>();

    for(int i=0;i<allbuttons.size();i++)
    {
        connect(allbuttons[i],SIGNAL(clicked()),this,SLOT(Button_is_clicked()));
    }
    connect(this->ui->resect,SIGNAL(clicked()),this,SLOT(Resect_is_clicked()));
    this->init_graph();
//    map.Showmap();


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::cat_move(int x,int y)
{
    QList<QPushButton *> allbuttons = this->findChildren<QPushButton *>();
    QString button_name = "ptn_"+ QString::number(x) + "_" + QString::number(y);
    for(int i=0;i<allbuttons.size();i++)
    {
        if(allbuttons[i]->objectName() == button_name)
        {
            int button_x = allbuttons[i]->x();
            int button_y = allbuttons[i]->y();
            this->ui->cat->setGeometry(button_x+5,button_y-10,this->ui->cat->width(),this->ui->cat->height());
        }
    }

}

void MainWindow::Button_is_clicked()
{

    QPushButton *button=qobject_cast<QPushButton*>(sender());
    if(button->objectName() == "ptn_" + QString::number(cat_map.x) + "_" + QString::number(cat_map.y))
    {
        this->ui->label->setText("请爱护小猫，障碍不能设在猫身上！");
    }
    else
    {
        button->setStyleSheet("border-radius:20px;background-color: rgb(64,65,66);");
        int i=0;
        int x,y;
        while(i < 121)
        {
              x = i/11;
              y = i%11;
              if(button->objectName() == "ptn_" + QString::number(x) + "_" + QString::number(y))
                  cat_map._map[x][y] = 100;
              i++;
        }
        switch (cat_map.Thinking())
        {
        case 0:this->ui->label->setText("您成功把我围住啦,请把我放出来!");break;          //猫被围住
        case 1:this->cat_move(cat_map.x,cat_map.y);break;  //继续
        case 2:this->ui->label->setText("溜了，溜了！");
            this->ui->cat->setGeometry(500,10,this->ui->cat->width(),this->ui->cat->height());break;   //猫跑了
        }
    }


}

void MainWindow::Resect_is_clicked()
{
    cat_map.~Create_map();
    cat_map = Create_map();

    init_graph();
}
void MainWindow::init_graph()
{
    QList<QPushButton *> allbuttons = this->findChildren<QPushButton *>();

    for(int i=0;i<allbuttons.size();i++)  //按钮全变为蓝色
    {
        allbuttons[i]->setStyleSheet("border-radius:20px;background-color: rgb(179,217,255);");
    }

    for(int x=0;x<11;x++)    //将随机障碍画在按钮上（即改变按钮的颜色）
    {
        for(int y=0;y<11;y++)
        {
            if(cat_map._map[x][y] == 100)
            {
                int i=0;
                while(i < 121)
                {

                      if(allbuttons[i]->objectName() == "ptn_" + QString::number(x) + "_" + QString::number(y))
                          allbuttons[i]->setStyleSheet("border-radius:20px;background-color: rgb(64,65,66);");
                      i++;
                }
            }
        }
    }
    this->ui->cat->setGeometry(this->ui->ptn_5_5->x()+5,this->ui->ptn_5_5->y()-10,this->ui->cat->width(),this->ui->cat->height());  //将猫画在（5，5）
    this->ui->label->setText("");

}


