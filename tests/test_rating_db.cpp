#include "../include/database/course_db.hpp"
#include "../include/database/database.hpp"
#include "../include/database/rating_db.hpp"
#include "../include/database/student_db.hpp"
#include "../include/database/teacher_db.hpp"
#include <gtest/gtest.h>

class RatingDBTest : public ::testing::Test {
protected:
  void SetUp() override {
    db = std::make_unique<database::Database>();

    studentDB = std::make_unique<database::StudentDB>(*db);
    courseDB = std::make_unique<database::CourseDB>(*db);
    teacherDB = std::make_unique<database::TeacherDB>(*db);
    ratingDB = std::make_unique<database::RatingDB>(*db);

    studentId =
        studentDB->addStudent({"Ivanov", "Ivan", "Ivanovich", "Institute",
                               "Department", 3, "Group", "12345"});

    courseId = courseDB->addCourse({1, "Math", "Mathematics"});
    teacherId = teacherDB->addTeacher(
        {1, "Petrov", "Petr", "Petrovich", "Mathematics", "Math Department"});
  }

  std::unique_ptr<database::Database> db;
  std::unique_ptr<database::StudentDB> studentDB;
  std::unique_ptr<database::CourseDB> courseDB;
  std::unique_ptr<database::TeacherDB> teacherDB;
  std::unique_ptr<database::RatingDB> ratingDB;

  int studentId;
  int courseId;
  int teacherId;
};

TEST_F(RatingDBTest, AddAndRetrieveRatings) {
  EXPECT_TRUE(ratingDB->addCourseRating(studentId, courseId, 5));
  EXPECT_TRUE(ratingDB->addTeacherRating(studentId, teacherId, 4));

  auto ratings = ratingDB->getAllRatings();
  ASSERT_EQ(ratings.size(), 2);
  EXPECT_EQ(ratings[0].getValue(), 5);
  EXPECT_EQ(ratings[1].getValue(), 4);
}
