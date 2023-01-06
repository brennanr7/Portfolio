###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Brennan Rivera

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow 
LDFLAGS  = -g3


CalcYouLater: DatumStack.o Datum.o RPNCalc.o main.o
	$(CXX) $(CXXFLAGS) -o CalcYouLater main.o DatumStack.o RPNCalc.o Datum.o

unit_test: DatumStack.o Datum.o DatumStack_tests.o \
	unit_test_driver.o
	$(CXX) $(CXXFLAGS) DatumStack_tests.o DatumStack.o unit_test_driver.o \
	Datum.o

DatumStack.o: DatumStack.h DatumStack.cpp Datum.h Datum.o
	$(CXX) $(CXXFLAGS) -c -o DatumStack.o DatumStack.cpp

DatumStack_tests.o: DatumStack_tests.cpp DatumStack.h DatumStack.cpp Datum.h \
	Datum.o
	$(CXX) $(CXXFLAGS) -c DatumStack_tests.cpp

unit_test_driver.o: unit_test_driver.cpp
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp

RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h
	$(CXX) $(CXXFLAGS) -c -o RPNCalc.o RPNCalc.cpp

main.o: main.cpp Datum.h RPNCalc.h DatumStack.h
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp
	
##
## Here is a rule for compiling .cyl files for testing
##
%.cylc:  %.cyl
	./cylc $^

clean:
	rm DatumStack.o testDatumStack.o unit_test_driver.o a.out
