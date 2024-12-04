#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::calculate_mean(){


}

void Widget::on_semesterOneAddButton_clicked()
{
    ui->semesterOneTable->insertRow(ui->semesterOneTable->rowCount());
}


void Widget::on_semesterOneDeleteButton_clicked()
{
    ui->semesterOneTable->removeRow(ui->semesterOneTable->currentRow());
}


void Widget::on_semesterTwoAddButton_clicked()
{
    ui->semesterTwoTable->insertRow(ui->semesterTwoTable->rowCount());
}


void Widget::on_semesterTwoDeleteButton_clicked()
{
    ui->semesterTwoTable->removeRow(ui->semesterTwoTable->currentRow());
}

