OS=$(shell uname -s)
CC=g++
STD=-std=c++17 -Wall -Wextra -Werror
LDFLAGS=--coverage
R=report
TDIR=tests
TNAME1=test_maze
TNAME2=test_cave
TFILE=$(TDIR)/$(TNAME1).cc $(TDIR)/$(TNAME2).cc
TOUT=$(TDIR)/$(TNAME).out
TFLAGS=-lgtest -lgtest_main
TARGET=model/*.cc
TRASH=../../build* *.out *.o *.dSYM $(TDIR)/*.gcda $(TDIR)/*.gcno *.out $(TDIR)/*.out report.* report/ *.gcno ../../Maze.tar.gz *.gcda $(TDIR)/.out *.user
BUILD_DIR= ../../build
APP_DIR = ../../app
MANUAL= Manual.texi

all: install
	@sleep 3
	open $(APP_DIR)/Maze.app

build:
	cmake -DCMAKE_PREFIX_PATH=$(QT_INSTALL_PREFIX) -B $(BUILD_DIR)
	make -C $(BUILD_DIR)

install: build
	mkdir -p $(APP_DIR)
	cp -rf $(BUILD_DIR)/Maze.app $(APP_DIR)

dist: clean
	cd .. && tar -zcvf ../Maze.tar.gz Maze

gcov_report: clean
	$(CC) $(LDFLAGS) $(STD) $(TFILE) $(TARGET) -o $(TOUT) $(TFLAGS)
	./$(TOUT)
	lcov -t "$(TNAME1) $(TNAME2)" --no-external -o $(R).info -c -d .
	genhtml -o $(R) $(R).info	
ifeq ($(OS), Darwin)	
	open -a "Google Chrome" $(R)/index.html
else
	google-chrome $(R)/index.html
endif	

install_gtest:
	sudo apt install -y libgtest-dev
	sudo apt install -y cmake
	cd /usr/src/gtest
	sudo cmake CMakeLists.txt
	sudo make
	sudo cp lib/*.a /usr/lib

style:
	clang-format --style=google -verbose -n model/*.cc model/*.h view/*.cc view/*.h controller/*.cc controller/*.h canvas/*.cc canvas/*.h

build_tests:
	cmake -S tests -B ../build_tests -DCMAKE_CXX_COMPILER=g++

create_tests: build_tests
	make -C ../build_tests Maze_tests

tests: create_tests
	./../build_tests/Maze_tests

clean:
	rm -rf $(TRASH)

dvi:
	mkdir -p $(APP_DIR)
	texi2pdf $(MANUAL).texi
	texi2html $(MANUAL).texi
	cp -r $(MANUAL).pdf $(APP_DIR)
	cp -r $(MANUAL).html $(APP_DIR)
	rm -rf $(MANUAL).aux $(MANUAL).log $(MANUAL).toc $(MANUAL).pdf $(MANUAL).html