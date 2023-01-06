/*
  * DatumStack
  *
  * by Brennan River, 03/06/2021
  *
  * An interface of the DatumStack that is the front end of the stack
  * used.
*/

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include <vector>
#include "Datum.h"

using namespace std;

class DatumStack {
  public:
  //constructors
  DatumStack();
  DatumStack(Datum j[], int size);
  //empty
  bool isEmpty();
  //clear
  void clear();
  //size
  int size();
  //top
  Datum top();
  //pop
  void pop();
  //push
  void push(Datum data);

  private:
  //vectpr of Datum elements
  vector<Datum> value;
};

#endif
