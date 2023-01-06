/*
 * main.cpp
 *
 * COMP 15 Project 2: the main program that opens the files and
 *                    communicates with the other programs.
 *
 * by [Brennan Rivera], [4/15/21]
 */

#include <iostream>
#include <ostream>
#include <string>
#include <fstream>

#include "CollabGraph.h"
#include "Artist.h"
#include "SixDegrees.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
      cerr << "Usage: ./SixDegrees dataFile [commandFile] [outputFile]"
           << endl;
      exit(EXIT_FAILURE);
    }
    //read in data from file
    SixDegrees func;
    func.populate(argv[1]);
    if (argc == 2) {
      func.runSixDegrees(cin, cout);
    }
    //open and use commandFile
    if (argc == 3) {
      string file = argv[2];
      func.commandFile(file, cout);
    }
    //command file and output file
    if (argc == 4) {
      ifstream filename;
      filename.open(argv[3]);
      if(not filename.is_open()) {
        cerr << argv[3] << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
      }

      ofstream output;
      output.open(argv[3]);
      if (output.fail()){
        cerr << argv[3] << " cannot be opened." << endl;
        exit(EXIT_FAILURE);
      }
      func.commandFile(argv[2], output);
      output.close();
      filename.close();
    }

    return 0;
}
