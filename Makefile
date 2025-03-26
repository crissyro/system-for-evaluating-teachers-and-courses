# Compiler and flags
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

# Installation paths
PREFIX := /usr/local
BIN_DIR := $(PREFIX)/bin
DESTDIR := # For staged installations

# Source files
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Formatting
FORMATTER := clang-format
FORMAT_STYLE := Google

# GNU standard targets
.PHONY: all install uninstall install-strip clean distclean \
maintainer-clean check installcheck dist check-style format \
docs html pdf dvi gcov_report rebuild TAGS

# Standard build targets
all: build

build: CXXFLAGS += $(RELEASE_FLAGS)
build: $(BUILD_DIR)/$(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: build

# Installation targets
install: build
	install -d $(DESTDIR)$(BIN_DIR)
	install -m 755 $(BUILD_DIR)/$(TARGET) $(DESTDIR)$(BIN_DIR)/$(TARGET)

install-strip: build
	install -d $(DESTDIR)$(BIN_DIR)
	install -s -m 755 $(BUILD_DIR)/$(TARGET) $(DESTDIR)$(BIN_DIR)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(BIN_DIR)/$(TARGET)

# Cleanup targets
clean:
	rm -rf $(BUILD_DIR) *.gcov *.gcda *.gcno

distclean: clean
	rm -rf $(DIST_DIR) $(DOCS_DIR) coverage.info

maintainer-clean: distclean
	rm -rf aclocal.m4 configure Makefile.in

# Testing targets
check: test
test: CXXFLAGS += $(COVERAGE_FLAGS)
test: LDFLAGS += $(COVERAGE_FLAGS)
test: build
	@$(MAKE) -C $(TEST_DIR) run-tests

installcheck: install
	@echo "Running post-installation checks..."
	@$(BUILD_DIR)/$(TARGET) --version

# Packaging targets
dist: distclean
	@mkdir -p $(DIST_DIR)
	tar -czvf $(DIST_DIR)/$(TARGET)_$(shell date +%Y%m%d).tar.gz \
	--transform "s,^,$(TARGET)/," --exclude=".*" *

# Code formatting targets
format:
	find $(SRC_DIR) include -name '*.hpp' -o -name '*.cpp' | xargs $(FORMATTER) -style=$(FORMAT_STYLE) -i

check-style:
	find $(SRC_DIR) include -name '*.hpp' -o -name '*.cpp' | xargs $(FORMATTER) -style=$(FORMAT_STYLE) --dry-run --Werror

# Documentation targets
docs: doxygen
doxygen:
	@mkdir -p $(DOCS_DIR)
	doxygen Doxyfile
	@echo "Documentation available at $(DOCS_DIR)/html/index.html"

pdf:
	@cd $(DOCS_DIR)/latex && make pdf

html:
	@$(MAKE) doxygen

# Coverage report
gcov_report: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory $(DOCS_DIR)/coverage
	@echo "Coverage report available at $(DOCS_DIR)/coverage/index.html"

# Helper targets
rebuild: clean build

TAGS:
	ctags -R .

# Dependency handling
-include $(OBJECTS:.o=.d)

# Build rules
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@