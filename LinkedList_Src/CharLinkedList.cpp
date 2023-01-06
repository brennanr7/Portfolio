/*
 * CharLinkedList.cpp
 *
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2021
 * edited by [Brennan Rivera], [2/11/21]
 *
 * Stores characters in a certain order. It imitates some functions of the
 * C++ string.
 *
 * NOTE: This is implemented using a doubly-linked list. It is not circular
 *       and does not have a "back" pointer.
 */

#include "CharLinkedList.h"

// for the print function
#include <iostream>

using namespace std;

/* Purpose: initializes an empty CharLinkedList */
CharLinkedList::CharLinkedList()
{
    // Initial each part of the doubly linked list
    len = 0;
    head = nullptr;
    tail = nullptr;
}

/*    Purpose: initializes a CharLinkedList containing one character
 * Parameters: the character that should be stored in the new list
 */
CharLinkedList::CharLinkedList(char c)
{
    // Create a new node for the character passed in
    n = new Node;
    len = 1;
    // Set the nodes data to the character passed in
    n->data = c;
    // Set the next and previous node to point to the nullptr
    n->next = nullptr;
    n->previous = nullptr;
    // Have the head and tail of the list point to the new node created
    head = n;
    tail = n;
}

/*    Purpose: initializes a CharLinkedList containing all of the specified
 *             characters, in the given order
 * Parameters: An array (in order) of characters to be stored in the list;
 *             the length of the given array (as an int)
 * Note: Size changes as a result to the size of the list passed in
 */
CharLinkedList::CharLinkedList(char *arr, int size)
{
    // First initialize the list
    len = 0;
    head = nullptr;
    tail = nullptr;
    // Go through the given characters and push back each one up until size
    for (int i = 0; i < size; i++) {
      pushAtBack(arr[i]);
    }
}

/* Purpose: copy constructor -- creates a list with the same information as
 *          the one passed in
 * Parameters: the other linked list address as a char
 * Returns: None
 * Note: Size changes as a result to the size of the list passed in
 */
CharLinkedList::CharLinkedList(const CharLinkedList &other)
{
    // Initializes an empty list
    len = 0;
    head = nullptr;
    tail = nullptr;
    // Go through the given list and push each element back at the index
    for (int i = 0; i < other.size(); i++) {
      pushAtBack(other.elementAt(i));
    }
}

/* Purpose: destructor -- frees all memory associated with the list
  * Parameters: None
  * Returns: None
  * Note: Memory is freed as a result to deleting each node
*/
CharLinkedList::~CharLinkedList()
{
    // Create a new node and set the node in order to traverse the list
    Node *curr_node = head;
    // Recurse through the list until the end and delete each node
    while (curr_node != nullptr) {
      curr_node = curr_node->next;
      delete head;
      head = curr_node;
    }
    // Delete the node pointed to head in order to free memory
    delete curr_node;
}

/* Purpose: assignment operator -- makes the current list contain the same
 *          information as the one on the right hand side
 * Parameters: The list as a constant char in order to  create the right hand
 *             side
 * Returns: The right hand side of the list
 */
CharLinkedList &CharLinkedList::operator =(const CharLinkedList &rhs)
{
    // if not the right hand side, we must clear the current list
    if (this != &rhs) {
      //clear curr list
        clear();

        // add each element from the other list into this one
        for (int i = 0; i < rhs.size(); i++) {
            pushAtBack(rhs.elementAt(i));
        }
    }
    return *this;
}

/* isEmpty
 *    Purpose: Check if the list is empty
 * Parameters: none
 *    Returns: a boolean -- true if the list is empty, false if it isn't
 */
bool CharLinkedList::isEmpty() const
{
    // If the head is the nullptr, then it is true there is an empty list
    if (head == nullptr) {
      return true;
    }
    // The list is not empty
    return false;
}

/* size
 *    Purpose: Get the number of characters being stored in the list
 * Parameters: none
 *    Returns: The number of characters currently stored in the list, as an
 *             int (will never be negative)
 */
int CharLinkedList::size() const
{
    // Return the length of the list
    return len;
}

/* first
 *    Purpose: Get the first element in the list.
 * Parameters: none
 *    Returns: The first element in the list, as a char.
 *
 *       Note: Prints an error message and exits if the list is empty.
 */
char CharLinkedList::first() const
{
    // Return the first nodes (head) data
    return head->data;
}

/* last
 *    Purpose: Get the last element in the list.
 * Parameters: none
 *    Returns: The last element in the list, as a char.
 *
 *       Note: Prints an error message and exits if the list is empty.
 */
char CharLinkedList::last() const
{
    // Create a new node set to the head in order to traverse the list
    Node *curr = head;
    // Traverse until at the end of the list (nullptr)
    while (curr->next != nullptr) {
      curr = curr->next;
    }
    // Return the last nodes data in the list
    return curr->data;
}

/* elementAt
 *    Purpose: Get the character at a given position.
 * Parameters: The index to be accessed, as an int. Should be in bounds; in
 *             other words, should be in the range [0, size() )
 *    Returns: The element at the specified index, as a char
 */
char CharLinkedList::elementAt(int idx) const
{
    // Edge case to ensure the list is not empty
    if (head == nullptr) {
      exit(EXIT_FAILURE);
    }
    // Ensure that the index given is in range
    if (idx > len || idx < 0) {
      std::cout << "Index (" << idx << ") not in range [0.." << len << ")"
      << std::endl;
      exit(EXIT_FAILURE);
    }
    // Make a new node pointed to the head in order to traverse the list
    Node *curr = head;
    // Set a counter to find the index at
    int num = 0;
    // Traverse the list until the num is equa to the index
    while (curr != nullptr) {
      if (num == idx) {
        return curr->data;
      }
      curr = curr->next;
      num++;
    }
    return curr->data;
}

/* print
 *    Purpose: Prints the list to the terminal (cout)
 * Parameters: None
 *    Returns: None
 */
void CharLinkedList::print() const
{
    // Create a new node set to head to traverse the list
    Node *curr = head;
    cout << "[CharLinkedList of size " << size();
    cout << " <<";
    // Traverse list and print each nodes data
    while (curr != nullptr) {
    cout << curr->data;
    curr = curr->next;
  }
  cout << ">>]" << endl;
}

/* clear
 *    Purpose: Makes the list empty
 *    Parameters: None
 *    Returns: None
 *    Note: Free's memory from the while list
 */
void CharLinkedList::clear()
{
    // Create a new node set to head in order to traverse the list
    Node *curr_node = head;
    // Traverse the list in order to delete each element
    while (curr_node != nullptr) {
      curr_node = curr_node->next;
      delete head;
      head = curr_node;
    }
    // Delete the node set to head
    delete curr_node;
}

/* pushAtBack
 *    Purpose: Adds a character to the back of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 *    Note: Increments the length/capacity by 1
 */
void CharLinkedList::pushAtBack(char c)
{
    // Create a new node for the given character
    Node *n = new Node;
    n->data = c;
    n->next = nullptr;
    // If the list is empty, the tail is n and head is n
    if (head == nullptr) {
      tail = n;
      head = n;
    }
    // Else we create a new node set to head and recurse till nullptr
    else {
      Node *curr = head;
      while (curr->next != nullptr) {
        curr = curr->next;
      }
      // Set the node with the given information to back of the list
      curr->next = n;
      // Doubly link the node to the node previous
      n->previous = curr;
      }
      // Increment capacity/length by 1
      len++;
}

/* pushAtFront
 *    Purpose: Adds a character to the front of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 *    Note: Increments the capacity/length by 1
 */
void CharLinkedList::pushAtFront(char c)
{
    // Create a new node for the given character
    Node *n = new Node;
    // Create the node and set the next to head
    n->data = c;
    n->next = head;
    // Set the new node to the head
    head = n;
    // Increment size
    len++;
}

/* insertAt
 *    Purpose: Adds a character to the list at a given position
 * Parameters: The character to be added to the list and the position at which
 *             it should be added. The position should be in-bounds, that is,
 *             in the range [0, size()]. Providing size() as the index will
 *             insert the character at the back of the list.
 *    Returns: None
 *    Note: New memory is allocated for the new node and the previous at the
 *          index, the length/capacity is incremented
 */
void CharLinkedList::insertAt(char c, int idx)
{
    // Error message printed if the index given is not in range
    if (idx > len || idx < 0) {
      std::cout << "Index (" << idx << ") not in range [0.." << size() << "]"
      << std::endl;
      exit(EXIT_FAILURE);
    }
    // Create a new node for the character passed in
    Node *n = new Node;
    n->data = c;
    n->next = nullptr;
    // Edge case if the head is the nullptr, we set both the head and tail = n
    if (head == nullptr) {
      head = n;
      tail = n;
    }
    // Edge case if the index is 0, call pushAtFront
    if (idx == 0) {
      pushAtFront(c);
      delete n;
      return;
    }
    // Create a node set to the head and num to 0 to traverse the list
    Node *curr = head;
    curr->previous = nullptr;
    int num = 0;
    //Traverse the list up until the nullptr and the index
    while (curr != nullptr && num < idx - 1) {
      curr = curr->next;
      num++;
    }
    // Set a new node to the current nodes information at the index
    Node *nd = curr->next;
    // Set the current node at the index to the node needed to insert
    curr->next = n;
    // Set the current nodes next to the node that was previously there
    curr = curr->next;
    curr->next = nd;
    // Increment lenth +1
    len++;
}

/* popFromFront
 *    Purpose: Removes the first element from the list
 * Parameters: None
 *    Returns: None
 *       Note: Prints an error message and exits if the list is empty and
 *             decrements the length/capacity by 1
 */
void CharLinkedList::popFromFront()
{
    // Error message printed if list is empty
    if(isEmpty()){
      cerr << "Cannot pop from an empty list" << endl;
      exit(EXIT_FAILURE);
    }
    // Create a new node pointed a the head and implement edge case if 1 node
    Node *curr = head;
    if (len == 1) {
      delete curr;
      len--;
      return;
    }
    // Set the new head to the previous head's next node and free previous head
    head = curr->next;
    delete curr;
    // Decrement length by 1
    len--;
}

/* popFromBack
 *    Purpose: Removes the last element from the list
 * Parameters: None
 *    Returns: None
 *       Note: Prints an error message and exits if the list is empty and
 *             decrements the length/size by 1
 */
void CharLinkedList::popFromBack()
{
    // Error message printed if is empty is true
    if(isEmpty()) {
      cerr << "Cannot pop from an empty list" << endl;
      exit(EXIT_FAILURE);
    }

    Node *curr = head;
    // Possible bug at this edge case when the length is 1
    if (len == 1) {
      delete curr;
      len--;
      return;
    }
    // Traverse the list right before we are at the end
    while (curr->next->next != nullptr){
      curr = curr->next;
    }
    // Free the last element in the list
    delete curr->next;
    curr->next = nullptr;
    // Decrement size by 1
    len--;
}

/* removeAt
 *    Purpose: Removes the element at a given index
 *    Parameters: The position at which to remove an element, which should be the
 *             index of an element currently in the list; in other words,
 *             should be in the interval [0, size)
 *    Returns: None
 *    Note: Capacity/length is decremented by 1 and memory is freed when
 *          removing the node at the index
 */
void CharLinkedList::removeAt(int idx)
{
    // Error message printed if index given is out of range
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    // Create a new node set to head in order to traverse the list
    Node *curr = head;
    if (idx == 0){ // Edge case if removing the head
      head = curr->next;
      delete curr;
      len--;
      return;
    }
    //Create node set to head and num set to 0 to traverse the list
    Node *n = head;
    int num = 0;
    // Traverse through the list until the base case or n is nullptr
    while (n != nullptr) {
      if (num == idx) {
        if (n->previous != nullptr) {   // We must check for our derefrensed
          n->previous->next = n->next; //  cases, if pass then we set the nodes
        }                             //   previous next to that nodes next
        else {
          popFromFront(); // We can just pop from front instead
          return;
        }
        if (n->next != nullptr) {         // Check for n's next node to be null,
          n->next->previous = n->previous;// if pass then we will set n's next
        }                                 // previous to n's previous node
        else {
          popFromBack(); // We can just pop from back instead
          return;
        }
        delete n; // Remove the node at the index and decrement size
        len--;
        return;
      }
      n = n->next;
      num++;
    }
}

/* replaceAt
 *    Purpose: Replaces the element at the given index with the given value
 * Parameters: A character to put in the list and the index of the
 *             element to replace. The index should be in-bounds, in the
 *             range [0, size() )
 *       Note: Prints an error message and exits if the index is out of bounds
 */
void CharLinkedList::replaceAt(char c, int idx)
{
    // Error message printed if index is out of range
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    //Create a new node with the character passed in
    Node *n = new Node;
    n->data = c;
    Node *curr = head; // Create a node set to head to traverse the list
    curr->previous = nullptr;
    int num = 0;
     // Traverse through the list to find the node at Index
    while (curr != nullptr && num < idx) {
      curr = curr->next;
      num++;
    }
    //insert the node at the index
    curr->data = n->data; // Set the node's data created to node at the index
    delete n; //Free memory allocated with the new node
}

/* concatenate
 *    Purpose: Adds the contents of a CharLinkedList to the back of the current
 *             one.
 * Parameters: A CharLinkedList whose contents should be pushed to the back of
 *             the current list. Will not be altered
 *    Returns: None
 */
void CharLinkedList::concatenate(const CharLinkedList &other)
{
    // Set size to the other size passed in
    int size = other.size();
    // Push back each element onto the list needed to concatenate
    for (int i = 0; i < size; i++) {
      pushAtBack(other.elementAt(i));
    }
}
