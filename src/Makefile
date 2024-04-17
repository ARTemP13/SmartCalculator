CC = gcc
TESTFLAGS_MAC = -lcheck -g
CFLAGS = -Wall -Wextra -Werror -std=c11
TESTFLAGS_LINUX = -lcheck -lm -lpthread -lrt -lsubunit -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: gcov_report install

test: s21_test_calc.c SmartCalc/*.c
	$(CC) $(CFLAGS) s21_test_calc.c SmartCalc/*.c -o test $(TESTFLAGS_MAC)
	./test

gcov_report:
	$(CC) $(GCOVFLAGS) $(CFLAGS) s21_test_calc.c SmartCalc/*.c -o test $(TESTFLAGS_MAC)
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	rm -rf gcovreport gcovreport.info *.gcda *.gcno *.dSYM *info
	open report/index.html

rebuild: clean all

clean: 
	rm -rf *.o test *.a a.out *.gcno *.gcda test.dSYM *.info report SmartCalculator dist

style_check:
	clang-format -style=Google -n *.c *.h *.c

style:
	clang-format -style=Google -i *.c *.h *.c

install: 
	mkdir SmartCalculator
	cd SmartCalculator && qmake ../SmartCalc && make

uninstall:
	rm -rf SmartCalculator

dvi:
	open ../README.md
dist:
	mkdir dist
	cp -R SmartCalc s21_test_calc.c Makefile dist
	cd dist && tar cvzf SmartCalc.tgz *
	cd dist && rm -rf *.c *.cpp *.h *.ui calc* SmartCalc Makefile
