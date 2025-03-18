CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -g -Iinclude -lsqlite3
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage
GTEST_FLAGS = -lgtest -lgtest_main -pthread

HEADERS = 
TEST_SRC = 
TEST_OBJ_DIR = obj
TEST_OBJ = $(patsubst tests/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC))
TEST_BIN = tests/tests
GCOV_REPORT_DIR = report
GCOV_OBJ_DIR = gcov_obj
GCOV_OBJ = $(patsubst tests/%.cpp,$(GCOV_OBJ_DIR)/%.gcov.o,$(TEST_SRC))

DOXYGEN_CONFIG = Doxyfile
DOXYGEN_OUTPUT_DIR = docs

.PHONY: all install uninstall build clean test \
dist docs dvi gcov_report rebuild format check_format doxygen clean_doxygen
