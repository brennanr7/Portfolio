CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -static-libstdc++
LDFLAGS  = -g3

MetroSim: main.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(CXXFLAGS) -o MetroSim main.o MetroSim.o PassengerQueue.o Passenger.o

main.o: main.cpp MetroSim.h PassengerQueue.h Passenger.h
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

MetroSim.o: MetroSim.h MetroSim.cpp PassengerQueue.h Passenger.h
	$(CXX) $(CXXFLAGS) -c -o MetroSim.o MetroSim.cpp

# This rule builds PassengerQueue.o
PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h
	$(CXX) $(CXXFLAGS) -c -o PassengerQueue.o PassengerQueue.cpp

# This rule builds Passenger.o
Passenger.o: Passenger.h Passenger.cpp
	$(CXX) $(CXXFLAGS) -c -o Passenger.o Passenger.cpp

# The below rules are used by unit_test
# This rule will be used by unit_test to build the tests for the
# PassengerQueue class.
unit_test: unit_test_driver.cpp PassengerQueue.cpp PassengerQueue.h \
					 PassengerQueue_tests.cpp Passenger.h Passenger.cpp MetroSim.cpp

	$(CXX) $(CXXFLAGS) unit_test_driver.cpp PassengerQueue.cpp \
PassengerQueue_tests.cpp Passenger.cpp MetroSim.cpp
# This rule builds the unit_test_driver.o file
# unit_test_driver.cpp will be copied for you when running unit_test.
# This driver will contain main()
unit_test_driver.o: unit_test_driver.cpp
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp

# This rule builds PassengerQueue_tests.o
PassengerQueue_tests.o: PassengerQueue_tests.cpp PassengerQueue.h Passenger.h
	$(CXX) $(CXXFLAGS) -c PassengerQueue_tests.cpp

# remove executables, object code, and temporary files from the current folder
# -- the executable created by unit_test is called a.out
clean:
	rm *.o *~ a.out
