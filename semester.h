#ifndef SEMESTER_H
#define SEMESTER_H

#include "subject.h"
#include <QVector>

class semester
{
public:
    semester();
    void add(const subject& sub);
    void remove(size_t index);
    void remove(const subject& sub);
    float mean();

private:
    QVector<subject> mSubjects;
};

#endif // SEMESTER_H
