#pragma once

namespace rating {

class Rating {
    int studentId;
    int entityId;
    int value;
    bool isCourse;
    
public:
    Rating(int sid, int eid, int val, bool isCourse)
        : studentId(sid), entityId(eid), value(val), isCourse(isCourse) {}
        
    int getStudentId() const { return studentId; }
    int getEntityId() const { return entityId; }
    int getValue() const { return value; }
    bool isCourseRating() const { return isCourse; }
    
}; // Rating

} // namespace rating