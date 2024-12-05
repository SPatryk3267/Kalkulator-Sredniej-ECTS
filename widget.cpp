#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QString>
#include <QLocale>
#include <QSizePolicy>
#include <QMessageBox>
#include "semester.h"
#include "subject.h"
#include <QBrush>
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>


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

    QMenuBar *menuBar = new QMenuBar(this);

    setup_menu(menuBar);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::setup_menu(QMenuBar* menu){

    QMenu *fileMenu = menu->addMenu("Plik");
    QAction *fileSaveAction = new QAction("Zapisz plik", this);
    QAction *fileExitAction = new QAction("Zamknij", this);
    fileMenu->addAction(fileSaveAction);
    fileMenu->addAction(fileExitAction);


    QMenu *editMenu = menu->addMenu("Edytuj");
    QAction *editExitAction = new QAction("Zamknij", this);
    editMenu->addAction(editExitAction);

    QMenu *viewMenu = menu->addMenu("Widok");
    QAction *viewExitAction = new QAction("Zamknij", this);
    viewMenu->addAction(viewExitAction);

    connect(fileExitAction, &QAction::triggered, this, &QWidget::close);
    connect(fileSaveAction, &QAction::triggered, this, &Widget::save_to_file);


    menu->setStyleSheet("QMenuBar { background-color: #F1F0F1; }"
                        "QMenuBar::item { padding: 5px; }"
                        "QMenuBar::item:selected { background-color: lightblue; }");

    ui->verticalLayout_4->setMenuBar(menu);
}

bool Widget::save_to_file(){
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Zapisz plik",
        "",
        "Pliki csv (*.csv);;Wszystkie pliki (*.*)"
        );

    if(filePath.isEmpty()){
        QMessageBox::warning(this, "Ostrzeżenie!", "Plik nie został zapisany");
        return 0;
    }

    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, "Ostrzeżenie!", "Błąd otwarcia pliku,\n plik nie został zapisany");
        file.close();
        return 0;
    }

    QTextStream fileOut(&file);

    fileOut << "semestr,przedmiot,ECTS,ocena\n";

    const QVector<subject>& subjectsOne = semesterOne.subjects();

    for(size_t i{}; i < subjectsOne.length(); i++){
        fileOut << 1 << ',' << subjectsOne[i].name() << ',' << subjectsOne[i].ects() << ',' << subjectsOne[i].grade() << '\n';
    }

    const QVector<subject>& subjectsTwo = semesterTwo.subjects();

    for(size_t i{}; i < subjectsTwo.length(); i++){
        fileOut << 2 << ',' << subjectsTwo[i].name() << ',' << subjectsTwo[i].ects() << ',' << subjectsTwo[i].grade() << '\n';
    }

    file.close();
    return 1;
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
        QString textData = table.item(row, column)->text();
        float floatData = textData.toFloat(&dataCorrect);
        switch (column) {
        case 0:
            semester[row].name() = textData;

            break;
        case 1:
            if(dataCorrect && floatData <= 30){
                semester[row].ects() = floatData;
                table.item(row, column)->setBackground(Qt::transparent);
            }
            else{
                table.blockSignals(true);
                table.item(row, column)->setBackground(QBrush(QColor(235, 0, 0, 193)));
                table.item(row, column)->setText("0");
                table.blockSignals(false);
                QMessageBox::warning(this, "Nieprawidłowe dane w tabeli", "Wprowadź poprawną liczbę w kolumnie ECTS.");
            }

            break;
        case 2:
            if(dataCorrect && floatData <= 6){
                semester[row].grade() = floatData;
                table.item(row, column)->setBackground(Qt::transparent);
            }
            else{
                table.blockSignals(true);
                table.item(row, column)->setBackground(QBrush(QColor(235, 0, 0, 193)));
                table.item(row, column)->setText("0");
                table.blockSignals(false);
                QMessageBox::warning(this, "Nieprawidłowe dane w tabeli", "Wprowadź poprawną liczbę w kolumnie Ocena.");
            }

            break;
        }
    }
}
