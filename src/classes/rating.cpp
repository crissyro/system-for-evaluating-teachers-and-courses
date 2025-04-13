#include "../../include/classes/rating.hpp"

namespace rating {

Rating::Rating(int sid, int eid, int val, bool isCourse)
    : studentId(sid), entityId(eid), value(val), isCourse(isCourse) {}

int Rating::getStudentId() const {
    return studentId;
}

int Rating::getEntityId() const {
    return entityId;
}

int Rating::getValue() const {
    return value;
}

bool Rating::isCourseRating() const {
    return isCourse;
}

}  // namespace rating