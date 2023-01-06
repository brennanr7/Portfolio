/*
  * RPNCalc
  *
  * by Brennan River, 03/06/2021
  *
  * An interface of the RPNCalc that allows the user to run the calculator
  * program
*/

#ifndef RPNCALC_H
#define RPNCALC_H

#include "Datum.h"
#include <vector>
#include "DatumStack.h"

class RPNCalc {
  public:
    //constructor
    RPNCalc();
    //descructor
    ~RPNCalc();
    //run
    void run(istream &data);
    //command num
    void numToStack(int num);
    //got_int
    bool got_int(string s, int *resultp);
    //print
    void print();
    //#t
    void commandT();
    //#f
    void commandF();
    //not
    void commandNot();
    //clear
    void clearStack();
    //drop
    void drop();
    //dup
    void dup();
    //swap
    void swap();
    //an operator
    void anOperator(string s);
    //comparing
    void comparing(string c);
    //parseRString
    void ParseRstring(istream &input);
    //exec
    void execCommand();
    //file command
    void commandFile();
    //if command
    void commandIf();

  private:
    DatumStack stack;
};

#endif
