/*
  * RPNCalc
  *
  * by Brennan River, 03/06/2021
  *
  * An implementation of the RPN CalcYouLater that allows the user to execute
  * commands through cin. This file uses the DatumStack as a stack data
  * structure to add elements given by the user
*/

#include "RPNCalc.h"
#include "Datum.h"
#include "DatumStack.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

/* RPNCalc
  *
  * Purpose: initializes objects of Datum
  * Parameters: none
  * Returns: none
*/
RPNCalc::RPNCalc()
{
}

/* ~RPNCalc
  *
  * Purpose: a descructor of the RPNCalc
  * Parameters: none
  * Returns: none
*/
RPNCalc::~RPNCalc()
{
}

/* run
  *
  * Purpose: reads in commands from standard input (cin) and each command is
  *          read as a string and commands will be seperated by white space
  * Parameters: istream data
  * Returns: none
*/
void RPNCalc::run(istream &data)
{
    string command;

    while(data >> command and command != "q") {
      //check if number was passed in
      if(command[0] >= 0 or command[0] <= 9 ) {
        int result;
        if(got_int(command, &result)) {
          numToStack(result);
        }
      }
      if(command == "#t") {
        commandT();
      }
      if(command == "#f") {
        commandF();
      }
      if(command == "not") {
        commandNot();
      }
      if(command == "print") {
        print();
      }
      if(command == "clear") {
        clearStack();
      }
      if(command == "drop") {
        drop();
      }
      if(command == "dup") {
        dup();
      }
      if(command == "swap") {
        swap();
      }
      if(command == "+" or command == "-" or command == "/" or command == "mod"
         or command == "*")
      {
        anOperator(command);
      }
      if(command == "<" or command == ">" or command == "<=" or command == ">="
         or command == "==") {
          comparing(command);
         }
      if(command == "{") {
        ParseRstring(data);
      }
      if(command == "exec") {
        execCommand();
      }
      if(command == "file") {
        commandFile();
      }
      if(command == "if") {
        commandIf();
      }
      if(command == "quit") {
        cerr << "Thank you for using CalcYouLater." << endl;
        exit(EXIT_SUCCESS);// exit program and pass valgrind
      }
    }
}

/* got_int
  *
  * Purpose: to check whether or not a string is an integer value
  * Parameters: the string and integer value of the string
  * Returns: a boolean true or false if the string is an integer
*/
bool RPNCalc::got_int(string s, int *resultp)
{
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/* numToStack
  *
  * Purpose: a datum containing a number to be pushed onto the stack
  * Parameters: an integer of the number
  * Returns: none
  * Note: stack size is incremented by one
*/
void RPNCalc::numToStack(int num)
{
    Datum type{num};
    stack.push(type);
}

/* print
  *
  * Purpose: To print the top of the stack without removing the top
  * Parameters: none
  * Returns: none
*/
void RPNCalc::print()
{     //check isEmpty
      try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
      Datum j = stack.top();
      string s = j.toString();
      cout << s << endl;
}

/* commandT
  *
  * Purpose: causes a Datum with the boolean true to be pushed on the stack
  * Parameters: none
  * Returns: none
  * Note: size of stack is incremented by 1
*/
void RPNCalc::commandT()
{
    bool t = true;
    Datum fact{t};
    stack.push(fact);
}

/* commandF
  *
  * Purpose: causes a Datum with the boolean false to be pushed on the stack
  * Parameters: none
  * Returns: none
  * Note: size of stack is incremented by 1
*/
void RPNCalc::commandF()
{
    bool f = false;
    Datum lie{f};
    stack.push(lie);
}

/* commandNot
  *
  * Purpose: pops the top element of the stack. a boolean, and pushes its
  *          boolean inverse
  * Parameters: none
  * Returns: none
*/
void RPNCalc::commandNot()
{   //check is empty
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum n = stack.top();
    string s = n.toString();
    if(s == "#t") { //check values of datum
      stack.pop();
      commandF();
    }
    else if(s == "#f") {
      stack.pop();
      commandT();
    }
    else if(s != "#f" or s != "#t") { //exception
      cerr << "Error: datum_not_bool" << endl;
    }
}

/* clearStack
  *
  * Purpose: clears the calculator by emptying the stack
  * Parameters: none
  * Returns: none
  * Note: size of the stack is reset to 0 and all elements in stack are erased
*/
void RPNCalc::clearStack()
{
    stack.clear();
}

/* drop
  *
  * Purpose: causes the top element on the stack to be removed
  * Parameters: none
  * Returns: none
  * Note: stack size is decremented by 1
*/
void RPNCalc::drop()
{   //check exception
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    stack.pop();
}

/* dup
  *
  * Purpose: duplicates the top element on the stack
  * Parameters: none
  * Returns: none
  * Note: size of stack is incremented by 1 and top element is duplicated
*/
void RPNCalc::dup()
{   //check exception
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum j = stack.top();
    Datum type{j};
    stack.push(type);
}

/* swap
  *
  * Purpose: swaps the top two elements on the stack
  * Parameters: none
  * Returns: none
*/
void RPNCalc::swap()
{   //check exception
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum first = stack.top(); //get first element
    stack.pop(); // pop the first element
    try{ //check exception
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum second = stack.top();
    stack.pop(); // get the second element and pop
    Datum one{first};
    stack.push(one);
    Datum two{second};
    stack.push(two);
}

/* anOperator
  *
  * Purpose: to take the two top elements as integers and have the operation
  *          performed by on them, and the result to be push on the top of
  *          the stack
  * Parameters: the operation as a string
  * Returns: none
  * Note: the stack size is reduced by one if the top two elements are
  *       integers and not 0
*/
void RPNCalc::anOperator(string s)
{   //check exception
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum first = stack.top();
    stack.pop();
    string f = first.toString();
    int resultF;
    int resultT;
    int total = 0;
    try{ //check exception
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    if (got_int(f, &resultF)) {
      Datum second = stack.top();
      string two = second.toString();
      stack.pop(); //access and pop element
      if (got_int(two, &resultT)) {
        if(s == "+") {
          total = resultF + resultT;
          numToStack(total);
        }
        if(s == "-") {
          total = resultT - resultF;
          numToStack(total);
        }
        if(s == "*") {
          total = resultT * resultF;
          numToStack(total);
        }
        if(s == "/") {
          if(resultT == 0 and resultF == 0) {
            cerr << "Error: division by 0." << endl;
          } else {
            total = resultT / resultF;
            numToStack(total);
          }
        }
        if(s == "mod") {
          if(resultT == 0 and resultF == 0) {
            cerr << "Error: division by 0." << endl;
          } else {
            total = resultT % resultF;
            numToStack(total);
          }
        }
      } else {
        cerr << "Error: datum_not_int" << endl;
      }
    } else {
      cerr << "Error: datum_not_int" << endl;
    }
}

/* comparing
  *
  * Purpose: to take the two top elements as integers and have the operation
  *          performed by on them, and the result true or false
  *          to be push on the top of the stack
  * Parameters: the comparison as a string
  * Returns: none
  * Note: the stack is decrimented by one if the top two elements are integers
*/
void RPNCalc::comparing(string c)
{   //check exception
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum first = stack.top();
    string f = first.toString();
    int resultF;
    int resultT;
    stack.pop();
    try{ //check exception
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum second = stack.top(); //access second elem to compare
    string two = second.toString();
    stack.pop();
    if(not first.isInt() and not second.isInt() and c == "==") {
      if(f == two) {
        commandT();
        return;
      } else {
        commandF();
        return;
      }
    }
    if (got_int(f, &resultF)) {
      if (got_int(two, &resultT)) {
        if(c == "<") {
          if(resultT < resultF){
            commandT();
          } else {
            commandF();
          }
        }
        if(c == ">") {
          if(resultT > resultF){
            commandT();
          } else {
            commandF();
          }
        }
        if(c == "<=") {
          if(resultT <= resultF){
            commandT();
          } else {
            commandF();
          }
        }
        if(c == ">=") {
          if(resultT >= resultF){
            commandT();
          } else {
            commandF();
          }
        }
        if(c == "==") {
          if(resultT == resultF){
            commandT();
          } else {
            commandF();
          }
        }
      } else {
        cerr << "Error: datum_not_int" << endl;
      }
    } else {
      cerr << "Error: datum_not_int" << endl;
    }
}

/* parseRString
  *
  * Purpose: to read from a stream until all curly braces are
  *          matched or until it reaches end of input
  * Parameters: input from the client (istream)
  * Returns: none
*/
void RPNCalc::ParseRstring(istream &input)
{
    string rstring;
    int numcurly = 1;
    string myRString = "{ ";
    string space = " ";
    // traversing through the input to check curly braces
    // rename pairs
    while(numcurly != 0 and not input.eof()) {
      input >> rstring;
      if (rstring == "}") {
        numcurly--;
      }
      if (rstring == "{") {
        numcurly++;
      }
      myRString = myRString + rstring + space; //add onto string to return
    }
    myRString = myRString.substr(0, myRString.length() - 1);//account for space
    Datum r{myRString};
    stack.push(r); //push rstring to stack
}

/* execCommand
  *
  * Purpose: to process the contents inside an rstring and return that element
  *          to the top of the stack
  * Parameters: none
  * Returns: none
  * Note: size of stack is changed depending on edge case or rstring
*/
void RPNCalc::execCommand()
{   //check exception
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum top = stack.top();
    stack.pop();
    string elem = top.toString();
    int num;
    if(got_int(elem, &num)) { //check for rstring
      cerr << "Error: cannot execute non rstring" << endl;
      return;
    }
    if(elem == "#t" or elem == "#f") { //check for rstring
      cerr << "Error: cannot execute non rstring" << endl;
      return;
    }
    //keep track of empty case
    if(elem.length() == 2) {
      return;
    }

    int length = elem.length() - 4;
    string sub = elem.substr(2, length);//get substring without braces
    istringstream my_stream(sub);
    run(my_stream);//take substring and execute
}

/* commandFile
  *
  * Purpose: to pop an rstring off the stack and reads in a file in the rstring
  *          and processes the commands in the file
  * Parameters: none
  * Returns: none
  * Note: size of stack is decremented to check the rstring
*/
void RPNCalc::commandFile()
{   //check exception
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum top = stack.top(); //access the rstring
    stack.pop();
    string elem = top.toString();
    int num;
    if(got_int(elem, &num)) { //check if not rstring
      cerr << "Error: file operand not rstring" << endl;
      return;
    }
    if(elem == "#t" or elem == "#f") { //check if not rstring
      cerr << "Error: file operand not rstring" << endl;
      return;
    }
    //keep track of empty case
    if(elem.length() == 2) {
      return;
    }
    //get the substring without the braces
    int length = elem.length() - 4;
    string file = elem.substr(2, length);
    ifstream filename;
    filename.open(file);
    if(not filename.is_open()) {
      cerr << "Unable to read " << file << endl;
    }
    run(filename);//pass the file to run
    filename.close();
}

/*
  *
  * Purpose: to pop off the top three elements on the stack, two rstrings and a
  *          boolean, and to check the boolean and compute either the false
  *          or true case assigned as the rstrings
  * Parameters: none
  * Returns: none
  * Note: size is changed depending on cases passed in
*/
void RPNCalc::commandIf()
{   //check exception
    try{
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum FalseCase = stack.top();//get the false case
    stack.pop();
    if(not FalseCase.isRString()) {
      cerr << "Error: expected rstring in if branch\n";
    }
    //get the second rstring (true case)
    try{ //check exception
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum TrueCase = stack.top();//get the true case
    stack.pop();
    if(not FalseCase.isRString()) {
      cerr << "Error: expected rstring in if branch\n";
    }
    //get the third element (boolean) use Datum.h
    try{//check exception
      if(stack.isEmpty()) {
        throw runtime_error("empty_stack");
      }
    }
    catch(const runtime_error&e) {
      cerr << "Error: empty_stack" << endl;
      return;
    }
    Datum condition = stack.top();
    stack.pop();
    //check the boolean
    if(not condition.isBool()) {
      cerr << "Error: expected boolean in if test\n";
      return;
    }
    if(condition.getBool()) {
      stack.push(TrueCase);//if true bool
      execCommand();
    } else {
      stack.push(FalseCase);//else false bool
      execCommand();
    }
}
