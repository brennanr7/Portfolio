/*
 * MetroSim.h
 *
 * by Brennan Rivera, 02/22/2021
 * Stores passengers as they board the train and stations. This is the front
 * of MetroSim and interacts with both the passenger.h and PassengerQueue.h
 * file to access passengers. This file contains the ordered list of passengers
 * stored in vectors.
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <vector>
#include <ostream>
#include <iostream>

class MetroSim
{
public:
    // constructurs
    MetroSim();
    // size of train
    int size();
    //edit queue
    void dequeue();
    // front
    Passenger front();
    //read in
    void read(string filename);
    //print stations
    void print_stations();
    // print the train
    void print_train();
    // run MetroSim
    void runMetroSim(ostream &output);
    // query p
    void query_p(int a, int d);
    // query m m
    void query_mm(ostream &output);
    // commandsFile
    void commandsFile(string file, ostream &output);

private:
    // vector of PassengerQueue's for the train
    vector<PassengerQueue> train;
    int stop;
    int idNum;
    // struct that creates the stations and their passengerqueues
    struct stations {
      PassengerQueue queue;
      int index;
      string name;
    };
    // vector of structs that stores the stations data
    vector<stations> stationData;
};

#endif
