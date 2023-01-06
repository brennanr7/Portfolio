* This program stores characters in a certain order. It imitates some functions of the C++ string demonstrated in both a dynamic array and linked list.



                            ---- FILES ----
I have included a total of seven files.

The {README file} is the file that contains the purpose of the program,
acknowledgments, the files provided, instructions on how to compile and run the
program, the type of data structure in use, the testing process, and the time
spent.

The {CharArrayList.h file} is the interface for the Array List. The file stores
characters in order. The contents of this file hold a class with both public
and private methods and variables. The public class helps to construct an empty
list, construct a list with a single character, construct a list with a given
list of characters and size, a copy constructor, an assignment operator
function that makes the current list the same as the right hand side, and a
destructor. Furthermore, the public class contains methods that help to get
information in the list, insert into the list, and edit the list. The private
section contains information in the dynamic array such as the data as a
pointer, the length, the capacity, and the private methods to shrink the
capacity and ensure capacity.

The {CharArrayList.cpp file} is the implementation of the CharArrayList.h file.
This file stores characters in a certain order which can be removed, added,
concatenated, and adjusted with its size.

The {CharLinkedList.h file} includes four constructors similar to the
CharArrayList.h file. This file will help to construct a clients list of
characters in a linked list format. This file will allow the client to get
information about list that won't modify the list, insert into the list, remove
from the list, concatenate orreplace the list. The private seccion allows
the clients information to be stored in a doubly linked list.

The {CharLinkedList.cpp file} is the implementation of the CharLinkedList.h
file. This file implements the methods from the .h file that allows the client
to store characters in certain orders as a linked list. The client is able
to edit the list with these implementations.

The {CharList_tests.cpp file} helped me implement each method as I did this
assignment. This file contains all the tests done for both .cpp files.

The {Makefile} allows each of the programs to link together. This includes
the test files for unit_testing.



                 ---- COMPILE / RUN INSTRUCTIONS ----
Simply type "unit_test" to run the unit tests for the CharArrayList
and CharLinkedList classes. This folder contains no driver, or
application, besides the unit tests for the list classes.

                ---- DATA STRUCTURES / ALGORITHMS ----
Data Structures used:

Array Lists- This data structure was used to implement a list of characters.
             This dynamic array was used in order to store characters given in
             a list. The Array List was implemented with a list of methods that
             access the elements in the list and change them. Specific features
             involved in this data structure include checks that see if the
             back of the array has room. Furthermore, the Array List is a
             linear data structure.
Advantages- Array lists are dynamic and can be changed. Array Lists have more
            efficient memory usages over a linked list since one pointer
            variable is needed for the entire list. Elements can be inserted
            and deleted at particular positions. Ablility to traverse the list.
Disadvantages- Data that is added or removed from the list effects the rest of
               the list, so the list must be updated. Array lists grow by a
               constant number, so copying the array is a disadvantage.

Linked Lists- This data structure was used to implement a list of characters
              similar to an array list but also very different. This dynamic
              data structure was used to store each character in nodes as
              pointers. This was benificial in the assignment because of the
              shape of the data structure being linear which stored characters
              in order.
Singly-Linked Advantages- Each data element is stored in its own node. Each
                          node is refrenced to the next. The head pointer
                          points to the first element while the tail pointer
                          points to the last element.
Singly Linked List Disadvantages- Linked Lists grow by a constant fact, so
                                  space is wasted in memory. Losing a pointer
                                  will not allow the use of any data it points
                                  to next. Traversing a linked list is done in
                                  one direction. When deleting a node, the data
                                  needs to refrence to the next node. Cannot
                                  access an element directly ulike an array
                                  list.
Doubly Linked Lists Advantages- Each node is refrenced to a next node and a
                                previous node. Doubly linked lists are able to
                                traverse to the next and the previous node.
Doubly Linked Lists Disadvantages- Extra memory is needed to point to the next
                                   node and the previous node. Unlike an array
                                   list, this data structure does allow the
                                   ability to access an element directly.

Singly linked vs. Doubly Linked- Singly linked lists only refrence the next
                                 node while doubly lists allow the refrence of
                                 the next and previous node. Someone may choose
                                 a doubly linked lsit over a singly in that
                                 specific advantage. Someone may use a singly
                                 linked list however when memory is an issue
                                 because a doubly linked list uses more memory.

My opinion- In my opinion while doubly linked lists use more memory than a
            singly linked list, it is better to use a doubly. I feel this is so
            because we are able to refrence the next node and the previous
            so we may traverse the list forwards and backwards.

                           ---- TESTING ----
As I wrote each individual method I would test the method in the
CharList_tests.cpp file. This would be done by constructing a list of characters
to both of the data structures and test each individual function as I wrote
them. For example, if I had just implemented pushAtBack(), I would construct
a list of characters first, then call pushAtBack, then print out the results
to see if I successfully implemented the function. As I was writing the
specifics of the code, I ran into certain bugs with edge cases, so I would
implement the edge cases and test in the function in the same way.
