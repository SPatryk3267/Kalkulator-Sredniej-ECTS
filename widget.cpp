#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QString>
#include <QLocale>
#include <QSizePolicy>
#include <QMessageBox>
#include "semester.h"
#include "subject.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->semesterOneTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->semesterTwoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(size_t i{}; i < 5; i++){
        semesterOne.add(subject());
        semesterTwo.add(subject());
    }

}

Widget::~Widget()
{
    delete ui;
}

QString Widget::round_to_two_decimal(float value){
    return QString::number(roundf((value) * 100) / 100);
}

void Widget::update_total_mean(){

    ui->meanResultSemesterBothLabel->setText(round_to_two_decimal((semesterOne.mean() + semesterTwo.mean()) / 2) );

}


void Widget::update_semester_one_mean(){

    ui->meanResultSemesterOneLabel->setText(round_to_two_decimal(semesterOne.mean()));
    update_total_mean();

}

void Widget::update_semester_two_mean(){

    ui->meanResultSemesterTwoLabel->setText(round_to_two_decimal(semesterTwo.mean()));
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
    validate_and_set_cell(*(ui->semesterOneTable), semesterOne, row, column);

    update_semester_one_mean();
}


void Widget::on_semesterTwoTable_cellChanged(int row, int column)
{
    validate_and_set_cell(*(ui->semesterTwoTable), semesterTwo, row, column);

    update_semester_two_mean();;
}

void Widget::validate_and_set_cell(QTableWidget& table, semester& semester, int row, int column){
    if(table.item(row, column)){
        bool dataCorrect;
        float data = table.item(row, column)->text().toFloat(&dataCorrect);
        switch (column) {
        case 1:
            if(dataCorrect){
                semester[row].ects() = data;
            }
            else{
                table.blockSignals(true);
                table.item(row, column)->setText("0");
                table.blockSignals(false);
                QMessageBox::warning(this, "Nieprawidłowe dane w tabeli", "Wprowadź poprawną liczbę w kolumnie ECTS.");
            }

            break;
        case 2:
            if(dataCorrect){
                semester[row].grade() = data;
            }
            else{
                table.blockSignals(true);
                table.item(row, column)->setText("0");
                table.blockSignals(false);
                QMessageBox::warning(this, "Nieprawidłowe dane w tabeli", "Wprowadź poprawną liczbę w kolumnie Ocena.");
            }

            break;
        }
    }
}
