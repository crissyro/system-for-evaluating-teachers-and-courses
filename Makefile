## @file
# @brief Makefile системы рейтингов университета
# @details Этот файл обеспечивает полный цикл управления проектом:
# - Сборка релизной/отладочной версий
# - Установка и деинсталляция
# - Проверка стиля кода
# - Генерация документации
# - Анализ покрытия кода тестами
# - Создание дистрибутива

###############################################################################
#                           Настройки компиляции                              #
###############################################################################

## @var CXX
# Используемый компилятор C++
CXX := g++

## @var CXXFLAGS
# Базовые флаги компиляции:
# - Стандарт C++17
# - Максимальный уровень предупреждений
# - Подключение директории include
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Iinclude

## @var LDFLAGS
# Флаги линковки:
# - Подключение библиотеки SQLite3
LDFLAGS := -lsqlite3

## @var DEBUG_FLAGS
# Флаги для отладочной сборки:
# - Генерация отладочной информации
# - Отключение оптимизаций
DEBUG_FLAGS := -g -O0

## @var RELEASE_FLAGS
# Флаги для релизной сборки:
# - Агрессивная оптимизация кода
RELEASE_FLAGS := -O3

## @var COVERAGE_FLAGS
# Флаги для анализа покрытия кода:
# - Генерация данных для gcov
COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage

###############################################################################
#                          Структура проекта                                  #
###############################################################################

## @var BUILD_DIR
# Директория для результатов сборки
BUILD_DIR := build

## @var SRC_DIR
# Директория с исходным кодом
SRC_DIR := src

## @var TARGET
# Имя исполняемого файла
TARGET := university_app

## @var DOCS_DIR
# Директория для документации
DOCS_DIR := docs

## @var DIST_DIR
# Директория для дистрибутивов
DIST_DIR := dist

## @var TEST_DIR
# Директория с тестами
TEST_DIR := tests

###############################################################################
#                          Настройки установки                                #
###############################################################################

## @var PREFIX
# Базовый путь для установки
PREFIX := /usr/local

## @var BIN_DIR
# Директория для установки бинарников
BIN_DIR := $(PREFIX)/bin

## @var DESTDIR
# Переменная для staged-установок
DESTDIR :=

###############################################################################
#                          Вспомогательные переменные                         #
###############################################################################

## @var SOURCES
# Автоматический поиск исходных файлов
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')

## @var OBJECTS
# Генерация списка объектных файлов
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

## @var FORMATTER
# Утилита для форматирования кода
FORMATTER := clang-format

## @var FORMAT_STYLE
# Стиль форматирования кода
FORMAT_STYLE := Google

###############################################################################
#                           Основные цели                                     #
###############################################################################

.PHONY: all install uninstall install-strip clean distclean \
maintainer-clean check installcheck dist check-style format \
docs html pdf dvi gcov_report rebuild TAGS

## @defgroup build_targets Цели сборки
# @{

## @brief Основная цель сборки (релизная версия)
all: build

## @brief Релизная сборка с оптимизацией
build: CXXFLAGS += $(RELEASE_FLAGS)
build: $(BUILD_DIR)/$(TARGET)

## @brief Отладочная сборка с символами
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: build

## @}

###############################################################################
#                           Цели установки                                    #
###############################################################################

## @defgroup install_targets Управление установкой
# @{

## @brief Установка приложения
install: build
	install -d $(DESTDIR)$(BIN_DIR)
	install -m 755 $(BUILD_DIR)/$(TARGET) $(DESTDIR)$(BIN_DIR)/$(TARGET)

## @brief Установка с удалением отладочных символов
install-strip: build
	install -d $(DESTDIR)$(BIN_DIR)
	install -s -m 755 $(BUILD_DIR)/$(TARGET) $(DESTDIR)$(BIN_DIR)/$(TARGET)

## @brief Деинсталляция приложения
uninstall:
	rm -f $(DESTDIR)$(BIN_DIR)/$(TARGET)

## @}

###############################################################################
#                           Цели очистки                                      #
###############################################################################

## @defgroup clean_targets Управление очисткой
# @{

## @brief Удаление временных файлов сборки
clean:
	rm -rf $(BUILD_DIR) *.gcov *.gcda *.gcno

## @brief Полная очистка проекта
distclean: clean
	rm -rf $(DIST_DIR) $(DOCS_DIR) coverage.info

## @brief Очистка для разработчиков
maintainer-clean: distclean
	rm -rf aclocal.m4 configure Makefile.in

## @}

###############################################################################
#                           Тестирование                                      #
###############################################################################

## @defgroup test_targets Тестирование
# @{

## @brief Запуск всех тестов (псевдоним для test)
check: test

## @brief Сборка и запуск тестов с анализом покрытия
test: CXXFLAGS += $(COVERAGE_FLAGS)
test: LDFLAGS += $(COVERAGE_FLAGS)
test: build
	@$(MAKE) -C $(TEST_DIR) run-tests

## @brief Проверка установленной версии
installcheck: install
	@echo "Running post-installation checks..."
	@$(BUILD_DIR)/$(TARGET) --version

## @}

###############################################################################
#                           Создание дистрибутива                             #
###############################################################################

## @defgroup dist_targets Упаковка
# @{

## @brief Создание дистрибутивного пакета
dist: distclean
	@mkdir -p $(DIST_DIR)
	tar -czvf $(DIST_DIR)/$(TARGET)_$(shell date +%Y%m%d).tar.gz \
	--transform "s,^,$(TARGET)/," --exclude=".*" *

## @}

###############################################################################
#                           Форматирование кода                               #
###############################################################################

## @defgroup format_targets Стиль кода
# @{

## @brief Автоматическое форматирование кода
format:
	find $(SRC_DIR) include -name '*.hpp' -o -name '*.cpp' | xargs $(FORMATTER) -style=$(FORMAT_STYLE) -i

## @brief Проверка стиля кода
check-style:
	find $(SRC_DIR) include -name '*.hpp' -o -name '*.cpp' | xargs $(FORMATTER) -style=$(FORMAT_STYLE) --dry-run --Werror

## @}

###############################################################################
#                           Документирование                                  #
###############################################################################

## @defgroup doc_targets Документация
# @{

## @brief Генерация HTML-документации
docs: doxygen

## @brief Генерация PDF-документации
pdf:
	@cd $(DOCS_DIR)/latex && make pdf

## @brief Псевдоним для генерации HTML
html:
	@$(MAKE) doxygen

## @}

###############################################################################
#                           Анализ покрытия                                   #
###############################################################################

## @defgroup coverage_targets Покрытие кода
# @{

## @brief Генерация отчета о покрытии
gcov_report: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory $(DOCS_DIR)/coverage
	@echo "Coverage report available at $(DOCS_DIR)/coverage/index.html"

## @}

###############################################################################
#                           Вспомогательные цели                              #
###############################################################################

## @defgroup helper_targets Вспомогательные цели
# @{

## @brief Полная пересборка проекта
rebuild: clean build

## @brief Генерация тегов для редакторов
TAGS:
	ctags -R .

## @}

###############################################################################
#                           Системные правила                                 #
###############################################################################

# Автоматическая генерация зависимостей
-include $(OBJECTS:.o=.d)

## @brief Основное правило сборки исполняемого файла
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

## @brief Правило компиляции объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@