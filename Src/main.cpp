/*
  * main
  *
  * by Brennan River, 03/06/2021
  *
  * An implementation of main that allows the user to run the program.
*/

#include "RPNCalc.h"
#include "Datum.h"
#include <iostream>
#include <string>

/* main
	*
	* Purpose: Run the calculator program
	* Parameters: none
*/
int main() {

  RPNCalc myCalc;
  myCalc.run(cin);

  return 0;
}
