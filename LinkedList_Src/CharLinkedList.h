/*
 * CharLinkedList.h
 *
 * COMP 15 homework 1
 * by C.R. Calabrese, January 2021
 * edited by [Brennan Rivera], [2/6/2021]
 *
 * One implementation of the CharList interface. Stores characters,
 * preserving their order and imitating some functionalities of the C++
 * std::string.
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H

class CharLinkedList {
    public:
        // constructors
        CharLinkedList();
        CharLinkedList(char c); // start with a single character
        // start with a list of characters
        CharLinkedList(char *arr, int size);
        // start with another CharList
        CharLinkedList(const CharLinkedList &other);
        // destructor
        ~CharLinkedList();
        // assignment operator overload
        CharLinkedList &operator =(const CharLinkedList &rhs);


        // CharList functions
        // get information about the list -- these won't modify the list
        bool isEmpty() const;
        int  size() const;
        char first() const;
        char last() const;
        char elementAt(int idx) const;
        void print() const;
        // insert into the list
        void pushAtBack(char c);
        void pushAtFront(char c);
        void insertAt(char c, int idx);
        // remove from the list
        void clear();
        void popFromFront();
        void popFromBack();
        void removeAt(int idx);
        // other ways to edit the list
        void replaceAt(char c, int idx);
        void concatenate(const CharLinkedList &other);

    private:
        // The structure of the list's nodes that containing the data, the
        // next node, and the previous node (doubly linked)
        struct Node {
          char data;
          Node *next;
          Node *previous;
        };
        //The lists head node, tail node, and length
        int len;
        Node *head;
        Node *tail;
        //Specific node that we can newly initialize
        Node *n;


};

#endif
