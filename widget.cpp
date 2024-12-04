#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QString>
#include <QLocale>
#include "semester.h"
#include "subject.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    for(size_t i{}; i < 5; i++){
        semesterOne.add(subject());
        semesterTwo.add(subject());
    }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::update_total_mean(){

    ui->meanResultSemesterBothLabel->setText(QString::number(roundf((semesterOne.mean() + semesterTwo.mean()) * 100) / 100 / 2));

}


void Widget::update_semester_one_mean(){

    ui->meanResultSemesterOneLabel->setText(QString::number(roundf((semesterOne.mean()) * 100) / 100));
    update_total_mean();

}

void Widget::update_semester_two_mean(){

    ui->meanResultSemesterTwoLabel->setText(QString::number(roundf((semesterTwo.mean()) * 100) / 100));
    update_total_mean();

}

void Widget::on_semesterOneAddButton_clicked()
{
    ui->semesterOneTable->insertRow(ui->semesterOneTable->rowCount());
    semesterOne.add(subject());
}


void Widget::on_semesterOneDeleteButton_clicked()
{
    qDebug() << ui->semesterOneTable->currentRow();
    if(ui->semesterOneTable->rowCount() > 0 && ui->semesterOneTable->currentRow() >= 0){
        semesterOne.remove(ui->semesterOneTable->currentRow());
        ui->semesterOneTable->removeRow(ui->semesterOneTable->currentRow());
        update_semester_one_mean();
    }
}


void Widget::on_semesterTwoAddButton_clicked()
{
    ui->semesterTwoTable->insertRow(ui->semesterTwoTable->rowCount());
    semesterTwo.add(subject());
}


void Widget::on_semesterTwoDeleteButton_clicked()
{
    if(ui->semesterTwoTable->rowCount() > 0 && ui->semesterTwoTable->currentRow() >= 0){
        semesterTwo.remove(ui->semesterTwoTable->currentRow());
        ui->semesterTwoTable->removeRow(ui->semesterTwoTable->currentRow());
       update_semester_two_mean();
    }
}

void Widget::on_semesterOneTable_cellChanged(int row, int column)
{

    switch (column) {
    case 0:
        if(ui->semesterOneTable->item(row, column)){
            semesterOne[row].name() = ui->semesterOneTable->item(row, column)->text();
        }
        break;
    case 1:
        if(ui->semesterOneTable->item(row, column)){
            semesterOne[row].ects() = ui->semesterOneTable->item(row, column)->text().toFloat();
        }
        break;
    case 2:
        if(ui->semesterOneTable->item(row, column)){
            semesterOne[row].grade() = ui->semesterOneTable->item(row, column)->text().toFloat();
        }
        break;
    }

    update_semester_one_mean();
}


void Widget::on_semesterTwoTable_cellChanged(int row, int column)
{
    switch (column) {
    case 0:
        if(ui->semesterTwoTable->item(row, column)){
            semesterTwo[row].name() = ui->semesterTwoTable->item(row, column)->text();
        }
        break;
    case 1:
        if(ui->semesterTwoTable->item(row, column)){
            semesterTwo[row].ects() = ui->semesterTwoTable->item(row, column)->text().toFloat();
        }
        break;
    case 2:
        if(ui->semesterTwoTable->item(row, column)){
            semesterTwo[row].grade() = ui->semesterTwoTable->item(row, column)->text().toFloat();
        }
        break;
    }

    update_semester_two_mean();;
}

