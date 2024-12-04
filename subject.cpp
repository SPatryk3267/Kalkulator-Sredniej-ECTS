#include "subject.h"


bool subject::operator==(const subject& other) const{

    return ((mName == other.mName) && (mEcts == other.mEcts) && (mGrade == other.mGrade));
}
