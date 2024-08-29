.PHONY: all calc
SHELL = /bin/sh
FLAGS=-std=c++17 -Wextra -Wall -Werror
# export PATH=/usr/local/Qt-6.6.2/bin:$PATH
SOURCES_TEST := $(wildcard 3d_viewer/test/*.cpp 3d_viewer/model/model.cpp  3d_viewer/model/utils/*.cpp)
LGFLAGS := -lgtest -lgtest_main


GCOV=-fprofile-arcs -ftest-coverage
TARGET=view
NAME=s21_3d_viewer
CC=gcc
TESTS=tests
OS := $(shell uname -s)
OS_TITLE=:=$(shell cat /etc/os-release)

ifeq ($(OS),Darwin)
    LCHECK := -lcheck
endif
ifeq ($(findstring Ubuntu, $(OS_TITLE)), Ubuntu)
    LCHECK=-lcheck -lsubunit -lm
else ifeq ($(findstring Manjaro, $(OS_TITLE)), Manjaro)
	LCHECK=-lcheck -lm
endif


all: clean install run

run:
	chmod +x ../build/$(TARGET).app
	open ../build/$(TARGET).app

install:       
	echo "Installation of $(TARGET).app:"
	mkdir -p ../build
	cd 3d_viewer/ && qmake && make && make clean && rm -rf Makefile && mv $(TARGET).app ../../build/$(TARGET).app
	echo "Installation completed! You can find app in the ../build/ folder!"

uninstall:
	rm -rf ../build
	echo "Uninstall completed!"
	
dist: install
	mkdir -p ../dist
	cp -R ../build/$(TARGET).app ../dist
	cp -R . ../dist/src
	cd ../dist && tar cvzf $(TARGET).tgz *
	cd ../dist && rm -rf $(TARGET).app
	rm -rf ../dist/src
	echo "Archive creation completed successfully!"	

dvi: clean
	@doxygen 3d_viewer/Doxyfile
	open doxygen/html/index.html
	

tests: clean
	g++ $(SOURCES_TEST) --coverage $(FLAGS) $(LGFLAGS) -o test -L.
	./test

gcov_report: tests
	gcov -f *.gcda
	lcov -t "test" -o test_full.info -c -d .
	lcov --extract test_full.info "$(PWD)/3d_viewer/model/utils/*.cpp" -o test_filtered.info
	genhtml -o report test_filtered.info
	open report/index.html


clean:
	rm -rf test *.o *.info *.gcov *.a report $(TESTS) *.gcda *.gcno coverage.info coverage_html doxygen valgrind.out ../build*

cleanall:
	rm -rf *.o *.gcov *.info doxygen ../build/$(TARGET).app *.a report a.out $(TESTS) *.gcda *.gcno coverage.info coverage_html doxygen valgrind.out build*


style:
	find . -iname '*.cpp' -o -iname '*.h' | xargs clang-format -style=google -i
	find . -iname '*.cpp' -o -iname '*.h' | xargs clang-format -style=google -n
