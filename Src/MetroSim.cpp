/*
 * MetroSim.cpp
 *
 * by Brennan Rivera, 02/22/2021
 * Stores passengers as they board the train, station, as well as running the
 * the simulation. Passengers are stored in a vector of queues, and a vector
 * of structs. This file uses MetroSim.h and PassengerQueue.h
 */

#include "MetroSim.h"
#include "PassengerQueue.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

/* MetroSim constructor
  *
  * Purpose: initializes the queue of the train and stations while setting
  *          the poistion of the train to 0 and id of passengers to 0
  * Parameters: none
  * Returns: none
*/
MetroSim::MetroSim()
{
    stop = 0;
    idNum = 0;
}

/* size
  *
  * Purpose: To return the size of the queue of the train
  * Parameters: none
  * Returns: The size of the queue as an integer
*/
int MetroSim::size()
{   // size of queue
    return train.size();
}

/* readMetro
  *
  * Purpose: read in the data of the specific file given
  * Parameters: the file given
  * Returns: none
  * Note: stationData pushes back strings from the file while train resizes
  *       to the size of the stationData
*/
void MetroSim::read(string filename)
{   // open and read in data
    ifstream input;
    string line;
    input.open(filename);
    if (input.fail()){
      cerr << "Error: could not open file " << filename << endl;
      exit(EXIT_FAILURE); //error statement if could not open file
    }
    //use get line and push back each string while incrimenting the index
    int i = 1;
    getline(input, line);
    while (not input.eof()) { //while not at the end of file
      stations myStation;
      myStation.name = line;
      myStation.index = i;
      stationData.push_back(myStation); //push back each structured station
      getline(input, line);
      i++;
    }
    input.close();
    // resize the train to be the size of stations
    train.resize(stationData.size());
}

/* print_stations
  *
  * Purpose: to print the display of the simulations to user
  * Parameters: none
  * Returns: none
*/
void MetroSim::print_stations()
{   // prints the passengers on the train
    cout << "Passengers on the train: " << "{";
    for (int i = 0; i < (int)train.size(); i++) {
       train.at(i).print(cout);
    }
     cout << "}" << endl;
    for (int i = 0; i < (int)stationData.size(); i++) {
      if (stop + 1 == stationData.at(i).index) { // if the train is at station
        cout << "TRAIN: " << "[" << stationData.at(i).index << "] ";
      } else {
        cout << "       " << "[" << stationData.at(i).index << "] ";
      }
        cout << stationData.at(i).name << " {";
        stationData.at(i).queue.print(cout);
        cout << "}" << endl;
    }
}

/* runMetroSim
  *
  * Purpose: the base of the simulation that allows the user to run commands
  *          through cin
  * Parameters: none
  * Returns: none
  *Note: passengerqueue vector, stationData vector, and train vector add
  *      elements depending upon the user input.
*/
void MetroSim::runMetroSim(ostream &output)
{   // command and arrival/ departure for query p
    string command = "";
    int arrival, departure;
    // while loop to continuously take in commands from the user
    while (command != "q") {
      print_stations(); // display the current state if the simulation
      cout << "Command? ";
      cin >> command;
      if (command == "p") {
        cin >> arrival;
        cin >> departure;
        query_p(arrival, departure); // takes the input to create a passenger
      }
      if (command == "m") {
        string c2;
        cin >> c2;
        if (c2 == "m") {
          query_mm(output); // moves the train while also displaying leaving
          //                   passengers to the output file
        }
        else if (c2 == "f") {
          cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
          return; // exits the simulation/program
        }
      }
    }
}

/* query_p
  *
  * Purpose: to enqueue a passenger to a station and a departure station
  *          of the users choice
  * Parameters: the arrival and departure station of the passenger
  * Returns: none
  * Note: Passenger is enqueued to a specific stationData while incrimenting
  *       the id of a new passenger
*/
void MetroSim::query_p(int a, int b)
{
  idNum += 1; //new passenger
  //create passenger
  Passenger myPassenger(idNum, a, b);
  //enqueue passenger
  stationData.at(a - 1).queue.enqueue(myPassenger);
}

/* query_mm
  *
  * Purpose: to move the train while also enqueing passengers at the train's
  *          stop and dequeing passengers based on their departure station
  *          while also dequeing the stations queue
  * Parameters: the output file for leaving passengers
  * Returns: none
  * Note: enqueues passengers to the train while dequeing the station's queue
  *     as well as deques passengers based on their departure and updates
  *     the train's index. Size of train and station queue may be changed
*/
void MetroSim::query_mm(ostream &output)
{ //if the train is at the last stop
    if (stop == 25) {
    //enqueue passengers to the train at index by their departure while
    //dequeing station
    int qsize = stationData.at(stop).queue.size();

    for (int i = 0; i < qsize; i++) {
      Passenger myPass = stationData.at(stop).queue.front();
      train.at(myPass.to - 1).enqueue(myPass);
      stationData.at(stop).queue.dequeue();
    }
    //deques specific passengers by their departure and sets stop to 0
    stop = 0;
    int tsize = train.at(stop).size();
     for (int i = 0; i < tsize; i++) {
       Passenger passleave = train.at(stop).front();
       output << "Passenger " << passleave.id << " left train at station ";
       output << stationData.at(stop).name << endl;
       train.at(stop).dequeue();
     }
  } else { //else we are not at the last stop
    //enques passengers at the stop while dequeues station
    int size = stationData.at(stop).queue.size();
    for (int i = 0; i < size; i++) {
      Passenger myPass = stationData.at(stop).queue.front();
      train.at(myPass.to - 1).enqueue(myPass);
      stationData.at(stop).queue.dequeue();
    }
     stop += 1; //update train index
     //deques specific passengers by their departure and prints to output file
     int dequeue_size = train.at(stop).size();
      for (int i = 0; i < dequeue_size; i++) {
        Passenger passleave = train.at(stop).front();
        output << "Passenger " << passleave.id << " left train at station ";
        output << stationData.at(stop).name << endl;
        train.at(stop).dequeue();
      }
  }
}

/* commandsFile
  *
  * Purpose: to run the commandFile given as argv[3] printed to output file
  * Parameters: the file name as a string
  * Returns: none
  * Note: passengerqueue vector, stationData vector, and train vector add
  *      elements depending upon the user input.
*/
void MetroSim::commandsFile(string file, ostream &output)
{   // inintialize our stream and commands
    ifstream input;
    string c1;
    string c2;
    int stationFrom;
    int stationTo;
    input.open(file); //open the file
    if (input.fail()){
      cerr << "Error: could not open file " << file << endl;
      exit(EXIT_FAILURE); // if could not open file, exit program
    }
    while(not input.eof()) {
      print_stations();
        cout << "Command? ";
        input >> c1; // exctract command from the file
        if (c1 == "p") {
          input >> stationFrom; // extract passenger to station
          input >> stationTo; // exact passenger destination
          query_p(stationFrom, stationTo); //create and enqueue passenger
        }
        if (c1 == "m") {
          input >> c2; //exctract command from the file
          if (c2 == "m") {
            query_mm(output); //move the metro
          }
          else if (c2 == "f") {
            cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
            return; //exit program
          }
        }
    }
    input.close(); // close the file
}
