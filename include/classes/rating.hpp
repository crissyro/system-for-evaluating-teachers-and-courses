#pragma once

namespace rating {

class Rating {
 private:
  int studentId;
  int entityId;
  int value;
  bool isCourse;

 public:
  Rating(int sid, int eid, int val, bool isCourse)
      : studentId(sid), entityId(eid), value(val), isCourse(isCourse) {}

  ~Rating() = default;

  inline int getStudentId() const { return studentId; }

  inline int getEntityId() const { return entityId; }

  inline int getValue() const { return value; }

  inline bool isCourseRating() const { return isCourse; }

};  // Rating

}  // namespace rating