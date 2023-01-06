/*
 * Passenger
 *
 * prints the passengers to the outputed data, communicates with Passenger.h
 */

#include <iostream>
#include <string>
#include "Passenger.h"

using namespace std;

/* print
 *
 * Purpose: To print the passenger information to the output stream
 * Parameters: the output stream to print the passengers
 * Returns: none
 */
void Passenger::print(ostream &output)
{
        // print passenger information to the output stream
        output << "[" << id << ", " << from << "->";
        output << to << "]";
}
