#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

    void calculate_mean();

    void on_semesterOneAddButton_clicked();

    void on_semesterOneDeleteButton_clicked();

    void on_semesterTwoAddButton_clicked();

    void on_semesterTwoDeleteButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
