#ifndef LINKEDLIST
#define LINKEDLIST
#include <iostream>
using namespace std;

#include "LListIter.h"

/************************************************************/
/*  Author:    	       	    Eve	Collier
/*  Course:    	       	    CSC	136
/*  Professor Name:    	    Carelli
/*  Assignment:        	    Project 4
/*  Filename:         	    LinkedList.h
/*
/*
/************************************************************/

// Need to prototype template classes 
// since they are referenced as friends below
template <typename T> class LListIter;

/////////////////////////////////////////////////////
// define a class to contain one linked list Node
template <typename T> 
class Node {  
  private:
    Node(T value=T(), Node* ptr=NULL) {
      data= value; next= ptr;
    }

    T getData() { return data; }
    void setData(const T& d) { data= d; }
    Node *getNext() { return next; }

    T data;
    Node *next;

    // must make LinkedList and LListIter friends to Node
    // otherwise, Node pointers will need to be passed around
    // allowing visiblity into LL elements
    friend class LinkedList<T>;
    friend class LListIter<T>;
};

/////////////////////////////////////////////////////
// the linked list class
template <typename T> 
class LinkedList {
  public:
    // Default constructor
    LinkedList();
    // destructor
    ~LinkedList();

    // add an item to the end
    void add(T); 
    // remove item with specified value
    bool remove(T);
    // delete everything
    void deleteAll();
    // replace an existing entry with given item
    bool replace(T);

    // Is the LinkedList empty?
    bool isEmpty();
    // find the max value in the list
    T findMax();
    // sort the list in ascending order
    void sortAscend();
    // find the min value in the list
    T findMin();
    // sort the list in descending order
    void sortDescend();
    // reverse the order of items in the list 
    void reverse();

    // get a copy of an entry
    T getEntry(T);

  private:
    // look for an item in the list
    Node<T>* findItem(T);

    // linked list pointer
    Node<T>* first;

    // extract item with specified value
    // return the extracted node
    Node<T>* extract(T);

    // make iterator a friend
    friend class LListIter<T>;
};
 
// Output a linked list, using a list iterator
template <typename T> 
ostream& operator<<(ostream &os,const LinkedList<T> &llist) {  
  LListIter<T>  iter(llist);
  if(!iter.end()) { 
    do {
      os << " " << *iter;
    } while(iter.next());
  }
  return os;
}

/////////////////////////////////////////////////////
// Linked List Implementations
/////////////////////////////////////////////////////

// Construct empty LinkedList
template <typename T> 
LinkedList<T>::LinkedList() {
  first= NULL;
}

// Free all Nodes
template <typename T> 
LinkedList<T>::~LinkedList() {
  deleteAll();
}

// is list empty?
// Note: inline !!!!!!!!!!!!
template <typename T> inline 
bool LinkedList<T>::isEmpty() {
  return (first == NULL);
}

// remove an item from the llist 
// return true if successful (false if not found)
template <typename T> 
bool LinkedList<T>::remove(T val) {  
  Node<T> *current= first;
  if(!isEmpty()) {
    // val is first item, remove it
    if(val == current->data) {
      first= current->next; delete current;
      return true;
    }
    // not the first, check the rest
    while(current->next != NULL) {
      if(val == current->next->data) {
        Node<T> *temp= current->next->next;
        delete current->next; current->next= temp;
        return true;
      }
      // not found, go on to the next one
      current= current->next;
    }
  }
  return false;
}

// Delete all Nodes in the linked list
template <typename T> 
void LinkedList<T>::deleteAll() {  
  Node<T> *ptr= first;
  while (ptr != NULL) {  
    Node<T> *doomed = ptr;
    ptr = ptr->next;
    delete doomed;
  }
}

// locate and return a copy of an item
template <typename T> 
T LinkedList<T>::getEntry(T val) {  
  Node<T> *ptr = first;
  while(ptr != NULL) {
    if(ptr->data == val) { 
       return ptr->getData(); 
    }
    ptr = ptr->next; 
  }
  return T();
}

// sort the linked list in ascending order
template <class T>
void LinkedList<T>::sortAscend() {
  Node<T> *nptr= NULL;
  Node<T> *lptr= nptr;

  while(!isEmpty()) {
    T data= findMax();
    lptr= nptr; nptr= extract(data); nptr->next= lptr;
  }
  first= nptr;
}

/////////////////////////////////////////////////////
//
// COMPLETE THE FOLLOWING METHODS !!!
//
/////////////////////////////////////////////////////

// The above code was provided by Carelli. Everything below was written by Eve :)


/************************************************************/
/*  Function name:    	    add()
/*  Description:    	    adds a new item to end of list
/*  Parameters:             T val
/*
/*  Return value:           void
/*
/*
/************************************************************/
template <typename T> 
void LinkedList<T>::add(T val) {
  // if list is empty, just add the node to the empty list
  if (isEmpty()){
    first = new Node <T>(val,first);
  }
  else{
  Node<T> *ptr = first;
  Node<T> *end = first;

  while(ptr != NULL) {
    end = ptr;
    ptr = ptr -> next;  // increment
  }

  end -> next =  new Node<T>(val, end -> next);  // add new node to end with added val
 }
} // END of add()


/************************************************************/
/*  Function name:          replace()
/*  Description:            replaces item in list with nitem
/*                          returns bool based on success
/*  Parameters:             T nitem
/*
/*  Return value:           bool
/*
/*
/************************************************************/
template <typename T> 
bool LinkedList<T>::replace(T nitem) {  
  // if list is empty, return false  
  if (isEmpty()){
    return false;
  }
  // else, proceed
  else{
  Node<T> *ptr = first;
  while (ptr != NULL){
    if(ptr -> data == nitem){
     ptr -> data = nitem;     // if data at current node is equal to what the user inputted
      return true;           // we can set it equal to the data in the node and return true
    }
    ptr = ptr -> next;      // increment
  }
 }
  return false;             // if we got to this point, no equal match was found.
} // END of replace()

/************************************************************/
/*  Function name:          extract()
/*  Description:            extracts item from list and 
/*     	       	       	    returns its pointer
/*  Parameters:             T val
/*
/*  Return value:           *LinkedList<T>
/*
/*
/************************************************************/	
template <typename T> 
Node<T> *LinkedList<T>::extract(T val) {
  Node<T> *current= first;
  Node<T> *trail= first;
  if(!isEmpty()) {
    // val is first item, remove it
    if(val == current->data) {
      first= trail->next; 
      return current;
    }
    
    // not the first, check the rest
    current = current -> next;   
    while(current != NULL) {
      if(val == current-> data) {
        trail -> next = current -> next;
        return current;
      }
      // not found, go on to the next one
      current= current->next;
      trail = trail -> next;
    }
  }  
  // if we've reached this point, the value is not in the list. Return NULL
  return NULL;
} // END of extract()

/************************************************************/
/*  Function name:          findMax()
/*  Description:            returns max val from list
/*     	       	       	    
/*  Parameters:             none
/*
/*  Return value:           LinkedList<T>
/*
/*
/************************************************************/
template <typename T>
T LinkedList<T>::findMax() {
  // if list is empty, return default val
  if (isEmpty()){
    return T();
  }

  else{
  Node<T> *ptr = first;
  Node<T> *max = first;

  while(ptr != NULL) {
    if (ptr -> data >= max -> data){  // if data in current node is larger than
       max = ptr;                     // max, max must be updated
    }
    ptr = ptr -> next;                 // increment
  }

  return max -> data;
 }
} // END of findMax()

/************************************************************/
/*  Function name:          reverse()
/*  Description:            reverses item order in list
/*     	       	       	    
/*  Parameters:             none
/*
/*  Return value:           void
/*
/*
/************************************************************/
template <class T>
void LinkedList<T>::reverse() {
  Node<T> *ptr= first;
  Node<T> *backwards= NULL;
  Node<T> *temp = NULL;

  while(ptr != NULL) {
    temp = ptr -> next;          //this holds the place for the next value
    ptr -> next = backwards;     // this makes our current pointer point to the node behind it in the list
    backwards = ptr;             // move pointer forward one  
    ptr = temp;                  // move pointer forward one 
  }
   first= backwards;            // move pointer forward one

} // END of reverse()

/************************************************************/
/*  Function name:          findMin()
/*  Description:            returns min val from list
/*
/*  Parameters:             none
/*
/*  Return value:           LinkedList<T>
/*
/*
/************************************************************/
template <typename T>
T LinkedList<T>::findMin() {
  // if list is empty, return default vals
  if (isEmpty()){
    return T();
  }
  else{
    Node<T> *ptr = first;
    Node<T> *min = first;

    while(ptr != NULL) {
      if (ptr -> data <= min -> data){   // if the data at val is smaller than min,
       min = ptr;                        // min must be updated
    }
    ptr = ptr -> next;                   // increment
  }
  return min -> data;
 } 

} // END of findMin()

/************************************************************/
/*  Function name:          sortDescend()
/*  Description:            sorts list in descending order
/*
/*  Parameters:             none
/*
/*  Return value:           void
/*
/*
/************************************************************/
// sort the linked list in descending order
template <class T>
void LinkedList<T>::sortDescend() {
  Node<T> *nptr= NULL;
  Node<T> *lptr= nptr;

  while(!isEmpty()) {
    T data= findMin();
    lptr= nptr; nptr= extract(data); nptr->next= lptr;
  }
  first= nptr;

} // END of sortDescend()


#endif
