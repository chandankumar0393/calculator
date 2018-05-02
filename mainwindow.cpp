#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

double firstNum;
bool typingsecondNumber=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_plusminus,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percentage,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pushButton_clear,SIGNAL(released()),this,SLOT(on_pushButton_clear_released()));
    connect(ui->pushButton_equal,SIGNAL(released()),this,SLOT(on_pushButton_equal_released()));

    connect(ui->pushButton_plus,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button=(QPushButton*)sender();
    double labelNumber;
    QString newlabel;
    if((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() || ui->pushButton_multiply->isChecked() ||
            ui->pushButton_divide->isChecked())&&(!typingsecondNumber))
    {
    labelNumber=button->text().toDouble();
    typingsecondNumber=true;
    newlabel=QString::number(labelNumber,'g',15);

    }
    else
    {
        if(ui->label->text().contains(".")&&button->text()=="0")
        {
            newlabel=ui->label->text()+button->text();
        }
        else
        {
        labelNumber=(ui->label->text()+button->text()).toDouble();
        newlabel=QString::number(labelNumber,'g',15);
        }
    }
    ui->label->setText(newlabel);
}

void MainWindow::on_pushButton_decimal_released()
{
    ui->label->setText(ui->label->text()+".");
}

void MainWindow::unary_operation_pressed()
{
   double labelNumber;
   QString newlabel;
   QPushButton *button=(QPushButton*)sender();

   if(button->text()=="+/-")
   {
       labelNumber=ui->label->text().toDouble();
       labelNumber=labelNumber * -1;
       newlabel=QString::number(labelNumber,'g',15);
       ui->label->setText(newlabel);
   }

   if(button->text()=="%")
   {
       labelNumber=ui->label->text().toDouble();
       labelNumber=labelNumber * 0.01;
       newlabel=QString::number(labelNumber,'g',15);
       ui->label->setText(newlabel);
   }
}



void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    typingsecondNumber=false;
    ui->label->setText("0");
}



void MainWindow::on_pushButton_equal_released()
{
    double labelNumber,secondNum;
    QString newlabel;

    secondNum=ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked())
    {
        labelNumber=firstNum + secondNum;
        newlabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_plus->setChecked(false);
    }

    else if(ui->pushButton_minus->isChecked())
    {
        labelNumber=firstNum - secondNum;
        newlabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_minus->setChecked(false);
    }

    else if(ui->pushButton_multiply->isChecked())
    {
        labelNumber=firstNum * secondNum;
        newlabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_multiply->setChecked(false);
    }

    else if(ui->pushButton_divide->isChecked())
    {
        labelNumber=firstNum / secondNum;
        newlabel=QString::number(labelNumber,'g',15);
        ui->label->setText(newlabel);
        ui->pushButton_divide->setChecked(false);
    }
    typingsecondNumber=false;
}

void MainWindow::binary_operation_pressed()
{
    QPushButton *button=(QPushButton*)sender();
    firstNum=ui->label->text().toDouble();
    button->setChecked(true);
}
