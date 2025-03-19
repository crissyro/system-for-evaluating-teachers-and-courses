CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS := -lsqlite3
DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O3
COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage

# Project structure
BUILD_DIR := build
SRC_DIR := src
TARGET := university_app
DOCS_DIR := docs
DIST_DIR := dist
TEST_DIR := tests

# Source files
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Installation paths
PREFIX := /usr/local
BIN_DIR := $(PREFIX)/bin

# Formatting
FORMATTER := clang-format
FORMAT_STYLE := Google

.PHONY: all install uninstall build clean test \
dist docs dvi gcov_report rebuild format check_format doxygen clean_doxygen

all: build

install: build
	install -d $(BIN_DIR)
	install -m 755 $(BUILD_DIR)/$(TARGET) $(BIN_DIR)

uninstall:
	rm -f $(BIN_DIR)/$(TARGET)

build: CXXFLAGS += $(RELEASE_FLAGS)
build: $(BUILD_DIR)/$(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: build

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(DOCS_DIR) $(DIST_DIR) *.gcov *.gcda *.gcno

test: CXXFLAGS += $(COVERAGE_FLAGS)
test: LDFLAGS += $(COVERAGE_FLAGS)
test: build
	@$(MAKE) -C $(TEST_DIR) run-tests

dist: build
	@mkdir -p $(DIST_DIR)
	tar -czvf $(DIST_DIR)/$(TARGET)_$(shell date +%Y%m%d).tar.gz -C $(BUILD_DIR) $(TARGET)

docs: doxygen

dvi:
	@echo "Generating DVI documentation..."
	@doxygen Doxyfile

gcov_report: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory $(DOCS_DIR)/coverage
	@echo "Coverage report available at $(DOCS_DIR)/coverage/index.html"

rebuild: clean build

format:
	find $(SRC_DIR) include -name '*.hpp' -o -name '*.cpp' | xargs $(FORMATTER) -style=$(FORMAT_STYLE) -i

check_format:
	find $(SRC_DIR) include -name '*.hpp' -o -name '*.cpp' | xargs $(FORMATTER) -style=$(FORMAT_STYLE) -output-replacements-xml | grep -q "<replacement " && echo "Formatting issues found" || echo "Formatting OK"

doxygen:
	@mkdir -p $(DOCS_DIR)
	doxygen Doxyfile
	@echo "Documentation available at $(DOCS_DIR)/html/index.html"

clean_doxygen:
	rm -rf $(DOCS_DIR)

# Дополнительные зависимости
-include $(OBJECTS:.o=.d)

# Автоматическая генерация зависимостей
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@