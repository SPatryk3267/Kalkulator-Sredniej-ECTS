#include "semester.h"
#include <cmath>
#include <QDebug>

semester::semester() { subjectCount = 0; }

void semester::add(const subject& sub){

    mSubjects.append(sub);
    subjectCount += 1;

}

void semester::remove(size_t index){

    if(index >= mSubjects.size()){
        throw std::out_of_range("Index out of range");
    }

    mSubjects.removeAt(index);
    subjectCount -= 1;

}

void semester::remove(const subject& sub){

    if(!mSubjects.contains(sub)){
        throw std::invalid_argument("Subject not found in the list");
    }

    mSubjects.removeOne(sub);
    subjectCount -= 1;

}


const float semester::mean() const{

    float gradeSum{};
    float ectsSum{};

    for(size_t i{}; i < mSubjects.size(); i++){
        gradeSum += mSubjects.at(i).grade() * mSubjects.at(i).ects();
        ectsSum += mSubjects.at(i).ects();
    }

    return gradeSum / ectsSum;

}

subject& semester::operator[](size_t index){

    return mSubjects[index];
}

const subject semester::operator[](size_t index) const{

    return mSubjects[index];
}
