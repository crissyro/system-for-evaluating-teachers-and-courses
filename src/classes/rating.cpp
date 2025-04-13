#include "../../include/classes/rating.hpp"

namespace rating {

Rating::Rating(int sid, int eid, int val, bool isCourse)
    : studentId(sid), entityId(eid), value(val), isCourse(isCourse) {}

inline int Rating::getStudentId() const {
    return studentId;
}

inline int Rating::getEntityId() const {
    return entityId;
}

inline int Rating::getValue() const {
    return value;
}

inline bool Rating::isCourseRating() const {
    return isCourse;
}

}  // namespace rating