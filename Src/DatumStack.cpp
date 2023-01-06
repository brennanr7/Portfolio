/*
  * DatumStack
  *
  * COMP 15 project 1
  * by Brennan River, 03/06/2021
  *
  * An implementation of the DatumStack that uses a stack data structure for
  * Datum of the RPN calculator. This file allows the user to access elements
  * in the stack, add elements onto the stack, and remove the stack
*/

#include "DatumStack.h"
#include <iostream>
#include <vector>

using namespace std;

/* DatumStack
  *
  * Purpose: to intialize an empty stack (done in the vector)
  * Parameters: none
  * Returns: none
*/
DatumStack::DatumStack()
{
}

/* DatumStack
  *
  * Purpose: creates a stack initialized so that the elements of the array are
  *          on the stack
  * Parameters: an array of Datum and an integer specifying the size of the
  *            array
  * Returns: none
  * Note: vector is resized to the size of the Datum array and elements are
  *       pushed on to the back of the vector
*/
DatumStack::DatumStack(Datum j[], int size)
{
    for (int i = 0; i < size; i++){
          value.push_back(j[i]);
    }
}

/* isEmpty
  *
  * Purpose: checks if the size of the vector is empty, returns true if so
  * Parameters: none
  * Returns: none
  * Note: the elements in the vector are erased and the size is also
  * decreased to 0
*/
bool DatumStack::isEmpty()
{
    if (value.size() == 0) {
      return true;
    }
    return false;
}

/* size
  *
  * Purpose: to get the size of the vector
  * Parameters: none
  * Returns: the size of the vector
*/
int DatumStack::size()
{
    return value.size();
}

/* clear
  *
  * Purpose: makes the current stack empty
  * Parameters: none
  * Returns: none
  * Note: the size and elements of the array are removed and set back to an
  *       empty stack
*/
void DatumStack::clear()
{
      value.erase(value.begin(), value.end());
}

/* pop
  *
  * Purpose: remove the top element on the stack
  * Parameters: none
  * Returns: none
  * Note: popping an element reduces the size by one and removes the element
*/
void DatumStack::pop()
{
    // do try catch in RPN calc
    try{
    if(isEmpty()) {
      throw runtime_error("empty_stack");
    }
  }
  catch(const runtime_error&e){
    cerr << "Error: empty_stack" << endl;
    return;
  }
    value.pop_back();
}

/* top
  *
  * Purpose: access and return the top datum in the stack
  * Parameters: none
  * Returns: the top of the stack
*/
Datum DatumStack::top()
{
      Datum v = value.at(value.size() - 1);
      return v;
}

/* push
  *
  * Purpose: to add an element to the top of the stack
  * Parameters: a Datum element
  * Returns: none
  * Note: the size of the stack is incrimented by 1
*/
void DatumStack::push(Datum data)
{
    value.push_back(data);
}
