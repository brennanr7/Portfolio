/*
 * CharArrayList.cpp
 *
 * edited by [Brennan Rivera], [02/6/2021]
 *
 * Stores characters in a certain order. It imitates some functions of the
 * C++ string.
 *
 * Notes: this implementation uses a dynamic array. So, potential
 * drawbacks as compared to the CharLinkedList class include slower insertions
 * and removals at the front of the list. On the other hand, since only one
 * pointer variable is needed for the entire list (as opposed to one pointer
 * per element in the CharLinkedList), the CharArrayList class has the
 * advantage of more efficient memory usage over the CharLinkedList.
 */

#include "CharArrayList.h"

// for print
#include <iostream>

using namespace std;

/* Purpose: initializes an empty CharArrayList */
CharArrayList::CharArrayList()
{
    len  = 0;
    cap  = 0;
    data = nullptr;
}

/*    Purpose: initializes a CharArrayList containing one character
 * Parameters: the character that should be stored in the new list
 */
CharArrayList::CharArrayList(char c)
{
    // initialize array
    len = 1;
    cap = 1;
    data = new char[cap];
    data[0] = c;
}

/*    Purpose: initializes a CharArrayList containing all of the specified
 *             characters, in the given order
 * Parameters: An array (in order) of characters to be stored in the list;
 *             the length of the given array (as an int)
 */
CharArrayList::CharArrayList(char *arr, int size)
{
    // initialize array with given size and characters
    len = size;
    cap = size;
    data = new char[cap];
    for (int i = 0; i < size; i++) {
      data[i] = arr[i];
    }
}

/* Purpose: copy constructor -- creates a list with the same information as
 *          the one passed in
 *
 *    Note: The array capacity may be different from the capacity of the list
 *          that is copied from. That is fine. What is important is that both
 *          lists will store the same information -- to the client, they will
 *          be the same.
 */
CharArrayList::CharArrayList(const CharArrayList &other)
{
    len = 0; // start with an empty list
    cap = 0;
    data = nullptr;

    // push each item from the other list onto this one
    for (int i = 0; i < other.size(); i++) {
        pushAtBack(other.elementAt(i));
    }
}

/* Purpose: destructor -- frees all memory associated with the list */
CharArrayList::~CharArrayList()
{
    // delete the data in the list
    delete [] data;
}

/* Purpose: assignment operator -- makes the current list contain the same
 *          information as the one on the right hand side
 *
 *    Note: The array capacity may be different from the list that is being
 *          copied from.
 */
CharArrayList &CharArrayList::operator =(const CharArrayList &rhs)
{
    if (this != &rhs) {
        clear(); // clear the current list

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
 *
 *       Note: "empty" refers to if the client is currently storing any
 *             information in the list. The capacity of the ArrayList is
 *             irrelevant.
 */
bool CharArrayList::isEmpty() const
{
    return size() == 0;
}

/* size
 *    Purpose: Get the number of characters being stored in the list
 * Parameters: none
 *    Returns: The number of characters currently stored in the list, as an
 *             int (but will never be negative)
 */
int CharArrayList::size() const
{
    return len;
}

/* first
 *    Purpose: Get the first element in the list.
 * Parameters: none
 *    Returns: The first element in the list, as a char.
 *
 *       Note: Prints an error and exits if the list is empty.
 */
char CharArrayList::first() const
{
    // if is empty = true, error message is printed
    if (isEmpty()) {
      std::cout << "Cannot get the last element of an empty list" << std::endl;
      exit(EXIT_FAILURE);
    }
    //we return the data at index 0
    return data[0];
}

/* last
 *    Purpose: Get the last element in the list.
 * Parameters: none
 *    Returns: The last element in the list, as a char.
 *
 *       Note: prints an error and exits if the list is empty.
 */
char CharArrayList::last() const
{
    // if is empty = true, error message is printed
    if (isEmpty()) {
      std::cout << "Cannot get the last element of an empty list" << std::endl;
      exit(EXIT_FAILURE);
    }
    //return the last character in the list [len - 1]
    return data[len - 1];
}

/* elementAt
 *    Purpose: Get the character at a given position.
 * Parameters: The index to be accessed, as an int. Should be in bounds; in
 *             other words, should be in the range [0, size() )
 *    Returns: The element at the specified index, as a char
 */
char CharArrayList::elementAt(int idx) const
{
    // error message if index is out of range
    if (idx > len || idx < 0) {
      std::cout << "Index (" << idx << ") not in range [0.." << size() << ")"
      << std::endl;
      exit(EXIT_FAILURE);
    }
    //return the data at the index given
    return data[idx];
}

/* print
 *    Purpose: Prints the list to the terminal (cout)
 * Parameters: None
 *    Returns: None
 */
void CharArrayList::print() const
{
    cout << "[CharArrayList of size " << size() <<  " <<";

    for (int i = 0; i < size(); i++) {
            cout << elementAt(i);
    }

    cout << ">>]" << endl;
}

/* clear
 *    Purpose: Makes the list empty
 * Parameters: None
 *    Returns: None
 *
 *       Note: Does not change the capacity of the array nor free any memory.
 */
void CharArrayList::clear()
{
    // Set the length to 0 to "clear" the list
    len = 0;
}

/* pushAtBack
 *    Purpose: Adds a character to the back of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharArrayList::pushAtBack(char c)
{
    // Edge case to ensure capacity
    if (len == cap) {
      ensureCapacity();
    }
    //add the element to the back of the list, increment size
    data[len] = c;
    len ++;
}

/* pushAtFront
 *    Purpose: Adds a character to the front of the list
 * Parameters: The character to be added to the list
 *    Returns: None
 */
void CharArrayList::pushAtFront(char c)
{
    // Edge case to ensure capacity
    if (len == cap) {
      ensureCapacity();
    }
    // Traverse to the front of the list
    for (int i = len; i > 0; i--) {
      data[i] = data[i - 1];
    }
    // Set the data given at the front, increment size
    data[0] = c;
    len++;
}

/* insertAt
 *    Purpose: Adds a character to the list at a given position
 * Parameters: The character to be added to the list and the position at which
 *             it should be added. The position should be in-bounds, that is,
 *             in the range [0, size()]. Providing size() as the index will
 *             insert the character at the back of the list.
 *    Returns: None
 */
void CharArrayList::insertAt(char c, int idx)
{
    // Error message printed if index given is not in range
    if (idx > len || idx < 0) {
      std::cout << "Index (" << idx << ") not in range [0.." << size() << "]"
      << std::endl;
      exit(EXIT_FAILURE);
    }
    // Ensure that there is capacity
    if (len == cap) {
      ensureCapacity();
    }
    // Traverse the list until the index is found
    for (int i = len; i > idx; i--) {
      data[i] = data[i - 1];
    }
    // Set the element given at the index, increment size
    data[idx] = c;
    len++;
}

/* popFromFront
 *    Purpose: Removes the first element from the list
 * Parameters: None
 *    Returns: None
 *
 *       Note: Prints an error message and quits if the list is empty
 */
void CharArrayList::popFromFront()
{
    // Confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    // Remove from the front of the list at index 0
    removeAt(0);
}

/* popFromBack
 *    Purpose: Removes the last element from the list
 * Parameters: None
 *    Returns: None
 *
 *       Note: Prints an error message and exits if the list is empty
 */
void CharArrayList::popFromBack()
{
    // Confirm list is non-empty
    if (isEmpty()) {
        cerr << "Cannot pop from an empty list" << endl;
        exit(EXIT_FAILURE);
    }
    // Remove from the back of the list
    removeAt(size() - 1);
}

/* removeAt
 *    Purpose: Removes the element at a given index
 * Parameters: The position at which to remove an element, which should be the
 *             index of an element currently in the list; in other words,
 *             should be in the interval [0, size)
 *    Returns: None
 *
 *       Note: If the amount of space in the array that is in use drops to less
 *             than one fourth, the array should be shrunk to half its size.
 */
void CharArrayList::removeAt(int idx)
{
    // Confirm index is in range
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    // Remove the element by shifting all subsequent elements to the left
    for (int i = idx; i < size() - 1; i++) {
        data[i] = data[i + 1];
    }
    // Update the length
    len--;

    // Check to shrink the array if appropriate
    checkShrink();
}

/* replaceAt
 *    Purpose: Replaces the element at the given index with the given value
 * Parameters: A character to put in the list and the index of the
 *             element to replace. The index should be in-bounds, in the
 *             range [0, size() )
 *
 *       Note: Prints an error message and exits if the index is out of bounds
 */
void CharArrayList::replaceAt(char c, int idx)
{
    // Error message printed if index given is out of range
    if (idx < 0 or idx >= size()) {
        cerr << "index " << idx << " not in range [0.." << size() << ")"
             << endl;
        exit(EXIT_FAILURE);
    }
    // Replace the data previous with the new data passed in
    data[idx] = c;
}

/* concatenate
 *    Purpose: Adds the contents of a CharArrayList to the back of the current
 *             one.
 * Parameters: A CharArrayList whose contents should be pushed to the back of
 *             the current list. Will not be altered
 *    Returns: None
 */
void CharArrayList::concatenate(const CharArrayList &other)
{
    // Set the size to the size of the list passed in
    int size = other.size();
    // Push each element to the back of the list to concatenate
    for (int i = 0; i < size; i++) {
         pushAtBack(other.elementAt(i));
    }
}

/* ensureCapacity
  *     Purpose: Expands the capacity of CharArrayList if called
  *     Parameters: None
  *     Returns: None
  *     Note: Will allocate memory for the new array capacity and delete the
  *           old memory
*/
void CharArrayList::ensureCapacity()
{
    int newCapacity = (cap * 2) + 2;

    //allocate new array on heap
    char *newArray = new char[newCapacity];

    //copy data over to new array
    for (int i = 0; i < len; i++) {
      newArray[i] = data[i];
    }
    //free the previous memory
    delete [] data;
    data = newArray;
    cap = newCapacity;
}

/* returnCapacity
  *     Purpose: Getter function that returns the capacity of the list
  *     Parameters: None
  *     Returns: The capacity of a list as an int
*/
int CharArrayList::returnCapacity()
{
    // Helper function to return capacity
    return cap;
}

/* checkShrink
  *       Purpose: Ensure that the size is not 1/4 of the capacity, if so the
  *                capacity is decrimented recursively until the size is not
  *                1/4 of the capacity
  *       Parameters: None
  *       Returns: None
  *       Note: Will shrink the capacity of the list
*/
void CharArrayList::checkShrink()
{
    //If the size is 1/4 of the capacity, recurse through until not
    if (cap/4 == size()) {
      cap--;
      checkShrink();
    }
}
