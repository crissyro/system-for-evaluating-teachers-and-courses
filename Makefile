## @file
# @brief Makefile системы рейтингов университета

###############################################################################
#                           Настройки компиляции                              #
###############################################################################

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS := -lsqlite3 -lpthread
DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O3
COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage

###############################################################################
#                          Структура проекта                                  #
###############################################################################

BUILD_DIR := build
SRC_DIR := src
TARGET := university_app
DOCS_DIR := docs
REPORT_DIR := report
DIST_DIR := dist
TEST_DIR := tests
DOXYFILE := Doxyfile
TEST_DB := $(TEST_DIR)/test.db

###############################################################################
#                          Настройки установки                                #
###############################################################################

BIN_DIR := bin
DESTDIR :=

###############################################################################
#                          Вспомогательные переменные                         #
###############################################################################

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_SOURCES := $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJECTS := $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_TARGET := $(BUILD_DIR)/university_tests

###############################################################################
#                           Основные цели                                     #
###############################################################################

.PHONY: all install uninstall clean distclean test gcov_report docs

all: build

build: CXXFLAGS += $(RELEASE_FLAGS)
build: $(BUILD_DIR)/$(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: build

###############################################################################
#                           Установка и очистка                               #
###############################################################################

install: build
	@mkdir -p $(BIN_DIR)
	cp $(BUILD_DIR)/$(TARGET) $(BIN_DIR)/
	zip -j $(BIN_DIR)/$(TARGET).zip $(BIN_DIR)/$(TARGET)

uninstall:
	rm -rf $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR) *.gcov *.gcda *.gcno $(TEST_DB)
	rm university.db

distclean: clean
	rm -rf $(DIST_DIR) $(DOCS_DIR) coverage.info

###############################################################################
#                           Тестирование и покрытие                           #
###############################################################################

test: CXXFLAGS += $(COVERAGE_FLAGS) -DTEST_DB_PATH=\"$(TEST_DB)\"
test: LDFLAGS += $(COVERAGE_FLAGS) -lgtest -lgtest_main
test: $(TEST_TARGET)
	@mkdir -p $(TEST_DIR)
	$(TEST_TARGET) --gtest_output=xml:$(BUILD_DIR)/test_results.xml

gcov_report: test
	lcov --capture --directory $(BUILD_DIR) --output-file coverage.info --ignore-errors mismatch
	lcov --remove coverage.info '/usr/*' '$(TEST_DIR)/*' --output-file coverage.info
	genhtml coverage.info --output-directory $(REPORT_DIR)/coverage

###############################################################################
#                           Документирование                                  #
###############################################################################

docs:
	doxygen $(DOXYFILE)

###############################################################################
#                           Форматирование кода                               #
###############################################################################

format:
	find $(SRC_DIR) include $(TEST_DIR) -name '*.hpp' -o -name '*.cpp' -exec clang-format -i -style=file {} \;

check-style:
	find $(SRC_DIR) include $(TEST_DIR) -name '*.hpp' -o -name '*.cpp' -exec clang-format --dry-run --Werror -style=file {} \;

###############################################################################
#                           Дистрибутив                                       #
###############################################################################

dist: distclean
	@mkdir -p $(DIST_DIR)
	tar -czvf $(DIST_DIR)/$(TARGET)_$(shell date +%Y%m%d).tar.gz \
	--transform "s,^,$(TARGET)/," --exclude=".*" *

###############################################################################
#                           Системные правила                                 #
###############################################################################

-include $(OBJECTS:.o=.d)
-include $(TEST_OBJECTS:.o=.d)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS))
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(TEST_DIR) -MMD -MP -c $< -o $@