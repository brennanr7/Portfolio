/*
  * parser
  *
  * by Brennan River, 03/06/2021
  *
  * An implementation that uses input stream to parse an rstring. This Includes
  * one function that reads input from a stream until matching curly braces
  * are found
*/

#include <iostream>
#include <string>
#include "DatumStack.h"
#include "Datum.h"

using namespace std;

/* parseRString
  *
  * Purpose: to read from a stream until all curly braces are
  *          matched or until it reaches end of input
  * Parameters: input from the client (istream)
  * Returns: the rstring as a string from the input
*/
string parseRString(istream &input)
{
    string rstring;
    int numcurly = 1;
    string myRString = "{ ";
    string space = " ";
    // traversing through the input to check curly braces
    while(numcurly != 0 || input.eof()) {
      input >> rstring;
      if (rstring == "}") {
        numcurly--;
      }
      if (rstring == "{") {
        numcurly++;
      }
      myRString = myRString + rstring + space; //add onto string to return
      }
    return myRString;
}
