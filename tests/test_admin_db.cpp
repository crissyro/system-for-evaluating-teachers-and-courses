#include <gtest/gtest.h>
#include <sqlite3.h>
#include "../include/database/admin_db.hpp"
#include "../include/database/database.hpp"

class AdminDBTest : public ::testing::Test {
protected:
    void SetUp() override {
        db = std::make_unique<database::Database>();
        adminDB = std::make_unique<database::AdminDB>(*db);
    }

    void TearDown() override {
        sqlite3_exec(db->getHandle(), "DELETE FROM admins;", nullptr, nullptr, nullptr);
    }

    std::unique_ptr<database::Database> db;
    std::unique_ptr<database::AdminDB> adminDB;
};

TEST_F(AdminDBTest, InitialAdminCreated) {
    EXPECT_TRUE(adminDB->checkCredentials("admin", "admin123"));
}

TEST_F(AdminDBTest, AddNewAdmin) {
    EXPECT_TRUE(adminDB->addAdmin("newadmin"));
    EXPECT_TRUE(adminDB->checkCredentials("newadmin", "admin123"));
}

TEST_F(AdminDBTest, CheckInvalidCredentials) {
    EXPECT_FALSE(adminDB->checkCredentials("admin", "wrongpass"));
    EXPECT_FALSE(adminDB->checkCredentials("nonexistent", "admin123"));
}

TEST_F(AdminDBTest, PreventDuplicateAdmins) {
    EXPECT_TRUE(adminDB->addAdmin("testadmin"));
    EXPECT_FALSE(adminDB->addAdmin("testadmin")); 
}