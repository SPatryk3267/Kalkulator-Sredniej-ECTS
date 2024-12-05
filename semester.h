#ifndef SEMESTER_H
#define SEMESTER_H

#include "subject.h"
#include <QVector>

class semester
{
public:

    semester();
    subject& operator[](size_t index);
    const subject operator[](size_t index) const;
    void add(const subject& sub);
    void remove(size_t index);
    void remove(const subject& sub);
    const float mean() const;
    QVector<subject>& subjects() { return mSubjects; }
    const QVector<subject>& subjects() const { return mSubjects; }
    const size_t length() const { return subjectCount; }

    void clear() {
        mSubjects.clear();
        subjectCount = 0;
    }

private:
    size_t subjectCount;
    QVector<subject> mSubjects;
};

#endif // SEMESTER_H
