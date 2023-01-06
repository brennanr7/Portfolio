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

                 ---- COMPILE / RUN INSTRUCTIONS ----
By typing make tree then doing ./tree, the code will run.

                ---- DATA STRUCTURES / ALGORITHMS ----
Data Structures used: The data structure used in hw3 is a binary search tree.
                      This data structure is useful to use sort order
                      traversal in the data. This makes it very sufficient to
                      traverse through a tree, insert into a tree, remove
                      from a tree, etc. A benifit  of the data
                      structure include maintaining records of data with less
                      space.


                           ---- TESTING ----
I used two main testing methods to ensure functionality of the program.
Problems that I ran into while testing consisted of creating two
main functions, insert and remove. The bugs I ran into when implementing these
functions related to conceptual errors. These errors were easily resolved by
drawing out and understand what was going on in the tree at a certain time.
Furthermore, I ran into memory erros in my insert function. This was resolved
by initialize the parents left and right node. 
