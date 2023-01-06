                           ---- PURPOSE ----
The purpose of the program is to construct a BinarySearchTree using a struct
that holds the data, the count, the left and right side of the tree.


                            ---- FILES ----
BinarySearchTree.h - This file includes the front end of the Binary Search
                     tree. This file holds private and public helper functions.

BinarySearchTree.cpp - The implementation of the BinarySearchTree.h file. This
                       file contains the implemented functions of a binary
                       search tree. It allows the user to insert into the
                       tree, remove nodes from the tree, and recieve
                       information about the tree.

Makefile - allows each of the programs to link together.

hw3.cpp - this file runs the binary search tree, displaying what is in the
          tree to the terminal.

add.cpp - this file includes additional tests to ensure functionality

                 ---- COMPILE / RUN INSTRUCTIONS ----
By typing make hw3 then doing ./hw3, the code will run.

                ---- DATA STRUCTURES / ALGORITHMS ----
Data Structures used: The data structure used in hw3 is a binary search tree.
                      This data structure is useful to use sort order
                      traversal in the data. This makes it very sufficient to
                      traverse through a tree, insert into a tree, remove
                      from a tree, etc. A benifit  of the data
                      structure include maintaining records of data with less
                      space.


                           ---- TESTING ----
I used two main testing methods to ensure functionality of the program. First,
I stated by using hw3.cpp to go about implementing each function while
ensuring that the function worked. In the order which I implemented these
functions in BinarySearchTree.cpp, was in the order of which main was
structured. Problems that I ran into while testing consisted of creating two
main functions, insert and remove. The bugs I ran into when implementing these
functions related to conceptual errors. These errors were easily resolved by
drawing out and understand what was going on in the tree at a certain time.
Furthermore, I ran into memory erros in my insert function. This was resolved
by initialize the parents left and right node. Once I completed hw3, I need
to diff against the demo program. After I was passed the demo program,
I then tested even more with the aditional file included: add.cpp. This
file was structued the same way as hw3.cpp but with additional testing
instances. When I tested this file, I would copy and past the contents
of the file into hw3.cpp and run the program to ensure functionality.
