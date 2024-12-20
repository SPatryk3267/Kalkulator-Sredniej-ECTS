#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QMenuBar>
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
    void setup_menu(QMenuBar* menu);

    void update_total_mean();

    void update_semester_one_mean();

    void update_semester_two_mean();

    QString round_to_two_decimal(float value);

    void validate_and_set_cell(QTableWidget& table, semester& semester, int row, int column);

    void table_clear(QTableWidget* table, semester& semester);

    void setup_tables();



private slots:

    void on_semesterOneAddButton_clicked();

    void on_semesterOneDeleteButton_clicked();

    void on_semesterTwoAddButton_clicked();

    void on_semesterTwoDeleteButton_clicked();

    void on_semesterOneTable_cellChanged(int row, int column);

    void on_semesterTwoTable_cellChanged(int row, int column);

    bool save_to_file();

    bool load_from_file();

    void reset_tables();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Widget *ui;
    semester semesterOne;
    semester semesterTwo;
    bool fileSaved = true;
    size_t startRowCount = 5;
};
#endif // WIDGET_H
