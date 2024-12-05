#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "semester.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    void setup_menu();

    void update_total_mean();

    void update_semester_one_mean();

    void update_semester_two_mean();

    QString round_to_two_decimal(float value);

    void validate_and_set_cell(QTableWidget& table, semester& semester, int row, int column);



private slots:

    void on_semesterOneAddButton_clicked();

    void on_semesterOneDeleteButton_clicked();

    void on_semesterTwoAddButton_clicked();

    void on_semesterTwoDeleteButton_clicked();

    void on_semesterOneTable_cellChanged(int row, int column);

    void on_semesterTwoTable_cellChanged(int row, int column);

    bool save_to_file();
private:
    Ui::Widget *ui;
    semester semesterOne;
    semester semesterTwo;
};
#endif // WIDGET_H
