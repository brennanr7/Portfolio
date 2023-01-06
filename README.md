* Program Purpose:

This project's purpose is to implement a Reverse Polish Notation calculator. In
order to to build the calculator we build a stack class that stores datum
elements.

* Files:

               DatumStack.cpp: The back end implementation of a stack data
               structure. This .cpp file allows the user to access elements in
               the stack, add elements onto the stack, and remove the stack.

               DatumStack.h: The front end interface of the DatumStack.cpp file
               which will initially construct the vector for the stack in the
               private section.

               parser.cpp: Includes a function that passes in input from a
               stream as parameters and reads the input until curly braces
               from the input are matched. Returned an rstring of the input.

               Datum.h: a link of the front of Datum class
               
               RPNCalc.cpp: The back end implementation of an RPN calculator.
               This file allows the user to execute commands through cin. The
               file uses the DatumStack as a stack data structure to store
               elements given by the user.

               RPNCalc.h: The front end interface of the RPNCalc.cpp file.
               This file allows the user to use certain commands in RPNCalc.

               main.cpp: This file allows the user to run the calculator
               program.
               

* Data Structures:

The data structure used I used were vectors and stacks. This is relevant in this
project because we need to store Datum elements in a container in LIFO order.
The Last in First out order was implemented with by storing each element
pushed back into the vector. Using a vector was optimal in this very way to
store each element in this order. Stacks are furthermore useful to store
elements in a linear format and in this project we need to access datum element
in this format. When adding to a stack, I knew I needed to implement this Data
structure with a vector because vectors are dynamic and we can easily add and
remove from the stack using a vector.
