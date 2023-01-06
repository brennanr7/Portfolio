/*
 * main.cpp
 *
 * COMP 15 homework 2
 * by Brennan Rivera, 02/22/2021
 * This file takes in arguments from the command line providing output files
 * as well as command files to run the program. Furthermore, main uses
 * other files to run the program.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "MetroSim.h"
#include "Passenger.h"
#include "PassengerQueue.h"

using namespace std;

/* main
	*
	* Purpose: Run the program simulation
	* Parameters: Command line arguments
*/
int main(int argc, char *argv[])
{
	if (argc < 3) {
    cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]" << endl;
    exit(EXIT_FAILURE);
  }
	//read in data from file
	MetroSim My_Sim;
 	My_Sim.read(argv[1]);
	//use of ofstream for outputfile
	ofstream output;
  output.open(argv[2]);
  if (output.fail()){
    cerr << "Error: could not open file " << argv[2] << endl;
    exit(EXIT_FAILURE);
  }
	//if there is a command file
	if (argc == 4) {
		My_Sim.commandsFile(argv[3], output); //commandline file
	} else {
		My_Sim.runMetroSim(output); //running metro from cin
	}
	//close the output file before exiting program
	output.close();

	return 0;
}
