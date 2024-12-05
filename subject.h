#ifndef SUBJECT_H
#define SUBJECT_H
#include <QString>

class subject
{
public:
    subject(QString name, float ects, float grade) : mName(name), mEcts(ects), mGrade(grade) {};
    subject() : subject("", 0, 0) {};

    bool operator==(const subject& other) const;

    QString& name(){ return mName; }
    const QString& name() const{ return mName; }
    float& ects(){ return mEcts; }
    const float& ects() const{ return mEcts; }
    float& grade(){ return mGrade; }
    const float& grade() const{ return mGrade; }

private:
    QString mName {""};
    float mEcts {};
    float mGrade {};
};

#endif // SUBJECT_H
