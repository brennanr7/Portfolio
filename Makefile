#
# Makefile for Binary Search Tree
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11


tree: BinarySearchTree.o
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
	rm -rf *.o *.dSYM
