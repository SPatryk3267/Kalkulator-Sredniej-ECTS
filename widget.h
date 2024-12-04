#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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

private slots:

    void update_mean();

    void on_semesterOneAddButton_clicked();

    void on_semesterOneDeleteButton_clicked();

    void on_semesterTwoAddButton_clicked();

    void on_semesterTwoDeleteButton_clicked();

    void on_semesterOneTable_cellChanged(int row, int column);

private:
    Ui::Widget *ui;
    semester semesterOne;
    semester semesterTwo;
};
#endif // WIDGET_H
