#
# Makefile for Binary Search Tree
#
# Homework 3 (fall 2021)
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11


hw3: hw3.o BinarySearchTree.o
	${CXX} -o $@ $^

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<

unit_test: unit_test_driver.o BinarySearchTree.o \
					 BinarySearchTree_tests.o
	${CXX} ${CXXFLAGS} BinarySearchTree.o unit_test_driver.o \
										 BinarySearchTree_tests.o

unit_test_driver.o: unit_test_driver.cpp
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp

clean:
	rm -rf hw3 *.o *.dSYM

provide:
	provide comp15 hw3 hw3.cpp BinarySearchTree.cpp BinarySearchTree.h \
	        README Makefile
