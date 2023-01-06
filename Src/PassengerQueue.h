/*
  * PassengerQueue.h
  *
  * by Brennan River, 02/22/2021
  *
  * An implementation of the passanger queues interface. We store passengers
  * IDs', arrival and destination. We will preserve the order of the queue
  * through the functions.
*/

#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include <iostream>
#include "Passenger.h"
#include <vector>

using namespace std;

class PassengerQueue {
    public:
      // getter
      Passenger front();
      // editing queue
      void dequeue();
      // editing queue
      void enqueue(const Passenger &passenger);
      // getter
      int size();
      // print
      void print(ostream &output);



    private:
      //need private vector to serve as queue base
      vector<Passenger> queue;
};

#endif
