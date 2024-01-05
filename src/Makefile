CC=g++ -std=c++17
CFLAGS_FOR_FUNC=-g -Wall -Wextra -Werror
ADD_CFLAGS=-g
LIBS=-lgtest -lpthread -lm
PATH-TO-QT=s21_Maze_App/s21_Maze/
GCOV_TEST = gcov_test
GCOV_DIR = report
TEST_TARGET = s21_Maze_test
OS=$(shell uname)

EXECUTABLE=dvi dist install clean


all: $(EXECUTABLE)

install:
	rm -rf temp
	rm -rf ../../s21_Maze_App
	mkdir temp
	cd temp; qmake ../s21_Maze_App/s21_Maze/s21_Maze.pro
	cd temp; make
	cd temp; make clean
	mkdir ../../s21_Maze_App
ifeq ($(OS), Darwin)
	cp temp/s21_Maze.app/Contents/MacOS/s21_Maze ../../s21_Maze_App/s21_Maze
else
	cp temp/s21_Maze ../../s21_Maze_App/s21_Maze
endif
	rm -rf temp
	../../s21_Maze_App/s21_Maze

uninstall:
	rm -rf temp
	rm -rf ../../s21_Maze_App

dist:
	rm -rf ../../s21_Maze_App-tar
	mkdir ../../s21_Maze_App-tar
	tar -cf ../../s21_Maze_App-tar/s21_Maze.tar Makefile $(PATH-TO-QT)*.*

dvi:
	rm -rf ../../s21_Maze_Pdf
	mkdir ../../s21_Maze_Pdf
	cp s21_Maze.pdf ../../s21_Maze_Pdf/s21_Maze.pdf


test:
	rm -rf test
	mkdir test
	cd test; qmake -Wnone ../s21_Maze_App/s21_Maze/s21_Maze_test.pro
	cd test; make
	cd test; make clean
ifeq ($(OS), Darwin)
	cp test/s21_Maze.app/Contents/MacOS/s21_Maze_test test/s21_Maze_test
	cd test; CK_FORK=no leaks -atExit -- ./s21_Maze_test
	cd test; lcov -t "s21_Maze_test" -o s21_Maze_test.info -c -d .
	cd test; lcov -r s21_Maze_test.info "/usr*" -o s21_Maze_test.info
	cd test; genhtml -o report s21_Maze_test.info
	cd test; open ./report/index.html
	cd test; rm -rf *.gcda *.gcno s21_Maze_test s21_Maze_test.info
    else
	cd test; valgrind --tool=memcheck --undef-value-errors=no ./s21_Maze_test
	cd test; lcov -t "s21_Maze_test" -o s21_Maze_test.info -c -d .
	cd test; lcov -r s21_Maze_test.info "/usr*" -o s21_Maze_test.info
	cd test; genhtml -o report s21_Maze_test.info
	cd test; xdg-open ./report/index.html
	cd test; rm -rf *.gcda *.gcno s21_Maze_test s21_Maze_test.info
endif

mem_test:
	rm -rf test
	mkdir test
	cd test; qmake -Wnone ../s21_Maze_App/s21_Maze/s21_Maze_test.pro
	cd test; make
	cd test; make clean
ifeq ($(OS), Darwin)
	cp test/s21_Maze.app/Contents/MacOS/s21_Maze_test test/s21_Maze_test
	cd test; CK_FORK=no leaks -atExit -- ./s21_Maze_test
    else
	cd test; valgrind --tool=memcheck --undef-value-errors=no ./s21_Maze_test
# cd test; valgrind --tool=memcheck --leak-check=full -s ./s21_Maze_test
endif

clean_all: clean clean_gcov

clean:
	rm -rf test

clean_gcov:
	cd test; rm -rf ./*.gcda ./*.gcno ./*.info ./$(GCOV_TEST) ./$(GCOV_DIR)


check:
	cd s21_Maze_App/s21_Maze; clang-format -i ./*.cc *.h
	cd s21_Maze_App/s21_Maze; clang-format -n ./*.cc *.h
