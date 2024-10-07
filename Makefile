CC=g++
PKGCONFIG = $(shell pkg-config --cflags --libs check)
CFLAGS=g++ -Wall -Wextra -Werror
CXXFLAGS=-std=c++17 -Wall -Werror -Wextra
FILES = Viewer/model/*.cc
OUT=a.out
TESTFILES= test/*.cc
GCOV = --coverage
CHECKFLAGS=-lcheck
OPEN_CMD=open
TEST_FGLAGS=-lgtest

ifeq ($(shell uname), Linux)
	TEST_FGLAGS=-lgtest -lgtest_main -pthread
endif

all: gcov_report install style_check dvi dist

gcov_report: clean
	unzip test_file.zip
	$(CC) $(GCOV) $(TESTFILES) $(FILES) -o gcov_report -lgtest -lstdc++ -std=c++17 -pthread
	./gcov_report
	lcov --no-external -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info exec a.out

tests: clean
	unzip test_file.zip
	@echo "\033[0;33m Preparing tests......\033[0m"
	$(CC) $(CXXFLAGS) $(TESTFILES) $(FILES) $(TEST_FGLAGS)
	./$(OUT)


install: uninstall
	mkdir Viewer/build
	cd Viewer/build && cmake ../../Viewer
	make -C ./Viewer/build/
	$(OPEN_CMD) ./Viewer/build/CurrentViewer.app

uninstall:
	rm -Rf Viewer/build/
	rm -rf Viewer.tar.gz

dvi:
	latex Viewer.tex
	dvipdfm Viewer.dvi
	$(OPEN_CMD) Viewer.pdf
	rm -rf Viewer.log Viewer.aux Viewer.dvi

dist: install
	tar -czf Viewer.tar.gz --directory=Viewer/ .

style:
	clang-format -style=google -i Viewer/model/*.cc Viewer/model/*.h
	clang-format -style=google -i Viewer/view/*.cpp Viewer/view/*.h
	clang-format -style=google -i Viewer/controller/*.cc Viewer/controller/*.h
	clang-format -style=google -i Viewer/memento/*.cc Viewer/memento/*.h
	clang-format -style=google -i Viewer/*.h Viewer/*.cpp
	clang-format -style=google -i test/*.cc

style_check:
	clang-format -style=google -n Viewer/model/*.cc Viewer/model/*.h
	clang-format -style=google -n Viewer/view/*.cpp Viewer/view/*.h
	clang-format -style=google -n Viewer/controller/*.cc Viewer/controller/*.h
	clang-format -style=google -n Viewer/memento/*.cc Viewer/memento/*.h
	clang-format -style=google -n Viewer/*.h Viewer/*.cpp
	clang-format -style=google -n test/*.cc

clean: uninstall
	rm -rf report tests/*.o ./a.out *.o *.gcda *.gcno *.info exec s21_viewer.a ./test_file *.dvi *.pdf gcov_report