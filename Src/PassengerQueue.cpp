/*
  * PassengerQueue.cpp
  *
  * by Brennan Rivera, 02/22/2021
  *
  * Stores passengers as they arrive at the station. Stored in LIFO
  * order.
  *
*/

#include "PassengerQueue.h"

#include <iostream>
#include <vector>

using namespace std;

/* dequeue
  *
  * Purpose: To remove the element at the front of the queue
  * Parameters: none
  * Returns: none
  * Note: decriments the size of the queue
*/
void PassengerQueue::dequeue()
{   //removing a passenger at the front of the queue
    queue.erase(queue.begin());
}

/* front
  *
  * Purpose: To return the element at the front of the queue
  * Parameters: none
  * Returns: The passenger at the front of the queue
*/
Passenger PassengerQueue::front()
{   //access the first passenger in the queue
    Passenger passenger = queue.front();
    return passenger;
}

/* size
  *
  * Purpose: To return the size of the queue
  * Parameters: none
  * Returns: The size of the queue as an integer
*/
int PassengerQueue::size()
{   // we return the queue size
    return queue.size();
}

/* enqueue
  *
  * Purpose: Adds a passenger to the queue at the back of the queue (LIFO)
  * Parameters: The passenger (ID, arrival, destination)
  * Returns: none
  * Note: Size increases as push_back is called
*/
void PassengerQueue::enqueue(const Passenger &passenger)
{   // adding passenger to the back of the queue
    queue.push_back(passenger);
}

/* print
  *
  * Purpose: To print the passengers in order of FIFO
  * Parameters: the output stream to print the passenger queue
  * Returns: none
*/
void PassengerQueue::print(ostream &output)
{
    //call passenger.print() and access each element in the queue
      for (int i = 0; i < (int)queue.size(); i++){
        queue.at(i).print(output);
    }
}
