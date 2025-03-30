#include "../include/database/course_db.hpp"
#include "../include/database/database.hpp"
#include <gtest/gtest.h>

class CourseDBTest : public ::testing::Test {
protected:
  void SetUp() override {
    db = std::make_unique<database::Database>();
    courseDB = std::make_unique<database::CourseDB>(*db);
  }

  void TearDown() override {
    sqlite3_exec(db->getHandle(), "DELETE FROM courses;", nullptr, nullptr,
                 nullptr);
  }

  std::unique_ptr<database::Database> db;
  std::unique_ptr<database::CourseDB> courseDB;
};

TEST_F(CourseDBTest, AddAndRetrieveCourse) {
  int id = courseDB->addCourse({1, "Test Course", "Computer Science"});
  auto course = courseDB->getCourse(id);

  EXPECT_EQ(course.getName(), "Test Course");
  EXPECT_EQ(course.getInstitute(), "Computer Science");
}

TEST_F(CourseDBTest, CourseExistenceCheck) {
  int id = courseDB->addCourse({2, "Math", "Mathematics Dept"});
  EXPECT_TRUE(courseDB->exists(id));
  EXPECT_FALSE(courseDB->exists(9999));
}

TEST_F(CourseDBTest, GetAllCourses) {
  courseDB->addCourse({3, "Course1", "Dept1"});
  courseDB->addCourse({4, "Course2", "Dept2"});

  auto courses = courseDB->getAllCourses();
  ASSERT_EQ(courses.size(), 5);
}