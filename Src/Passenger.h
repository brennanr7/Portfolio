/*
 * Passenger
 *
 * by Brennan Rivera, 02/22/2021
 * Creates the passenger to be enqueued in a list of passengerquues
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>


struct Passenger
{

        int id, from, to;

        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        // print the passenger created
        void print(std::ostream &output);

};

#endif
