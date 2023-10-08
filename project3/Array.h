#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cassert>
using namespace std;

////////////////////////////////////////////////////////////////////////
//
//   Author:           Eve Collier 
//   Creation Date:    November 8, 2022 
//   Due Date:         November 15, 2022
//   Course:           CSC136
//   Professor Name:   Dr. Carelli 
//   Assignment:       Project 3
//   Filename:         Array.h 
//
//   Purpose:        
//      This program will use a provided Array<dataType> class to 
//      handle situations in which the internally stored array
//      is used PARTIALLY filled
//
////////////////////////////////////////////////////////////////////////




template <class dataType> 
class Array {
public:
  Array(int size= 3);                // default constructor
  Array(const Array&);               // copy constructor
  Array(const dataType[], int, int); // construct from an dataType array
  ~Array();                          // destructor
  
  int getCapacity() const { return capacity; }
  int getNumUsed() const { return numUsed; }

  const Array<dataType> &operator=(const Array &); // assignment

  Array<dataType> &operator+=(dataType); // append element to array
  Array<dataType> &operator++();         // preincrement - add default to front
  Array<dataType> operator++(int);       // postincrement - add default to front

  bool operator==(const Array &) const;  // compare if equal
  bool operator>(const Array &) const;   // just number used

  dataType &operator[](int);             // l-value subscript operator
  const dataType &operator[](int) const; // r-value subscript operator

  dataType operator*() const;            // dereference operator

private:
  int capacity;              // capacity of the array
  int numUsed;               // number of elements in use
  dataType *ptr;             // pointer to first element of array
};

////////////////////////////////////////////////////////////////////////
//
//   Method name:      default constructor
//   Description:      Provides default values for an array 
//   Member Type:      Constructor
//   Parameters:       int size
//   Return Value:     none 
//
////////////////////////////////////////////////////////////////////////
 
template <class dataType> 
Array<dataType>::Array(int size) {
  capacity= size;
  numUsed= 0;
  
  ptr = new dataType[capacity]; // create space for array
  assert( ptr != 0 );    // terminate if memory not allocated

  // initialize to default value
  for (int i = 0; i < capacity; ++i) ptr[i]= dataType();

} // END of default constructor


////////////////////////////////////////////////////////////////////////
//
//   Method name:      initalizing constructor
//   Description:      initalizes values from a standard array
//   Member Type:      Constructor
//   Parameters:       const dataType A[], int cap, and int num2copy
//   Return Value:     none                  
//
////////////////////////////////////////////////////////////////////////


// constructor initializes from a standard array
// designate the number of elements to copy (must be <= capacity)
template <class dataType>
Array<dataType>::Array(const dataType A[], int cap, int num2copy) {
  assert(cap > 0 && num2copy <= cap);
  numUsed= 0;

  // replace what follows
  capacity= cap; 
  numUsed = num2copy;

  ptr = new dataType[capacity]; // create space for array
  assert( ptr != 0 );    // terminate if memory not allocated
  assert ( numUsed < capacity); // terminate if numUsed < capacity
 
   for (int i = 0; i < numUsed; ++i){
     ptr[i] = A[i]; 
   }

} // END of constructor	initalizing from standard array


////////////////////////////////////////////////////////////////////////
//
//   Method name:      copy constructor
//   Description:      Performs a deep copy of one object to another
//   Member Type:      Constructor
//   Parameters:       const Array &A
//   Return Value:     none                  
//
////////////////////////////////////////////////////////////////////////

// Copy constructor for class Array
// must receive a reference to prevent infinite recursion
template <class dataType> 
Array<dataType>::Array(const Array &A) {  
  // an existing array will be
  capacity= A.capacity;
  numUsed = A.numUsed;
  ptr = new dataType[capacity]; // create space for array
  assert( ptr != 0 );    // terminate if memory not allocated

  for ( int i = 0; i < capacity; i++ )
     ptr[ i ] = A.ptr[ i ];  // copy init into object

} // END of copy constructor

////////////////////////////////////////////////////////////////////////
//
//   Method name:      destructor
//   Description:      reclaims memory space
//   Member Type:      Destructor
//   Parameters:       none
//   Return Value:     none                  
//
////////////////////////////////////////////////////////////////////////

template <class dataType> 
Array<dataType>::~Array() {
  delete [] ptr;            // reclaim space for array
} // END of destructor

////////////////////////////////////////////////////////////////////////
//
//   Method name:      =
//   Description:      Overloads = operator
//   Member Type:      Operator overload
//   Parameters:       const Array &right
//   Return Value:     none                  
//
////////////////////////////////////////////////////////////////////////

// Overloaded assignment operator
template <class dataType> 
const Array<dataType> &Array<dataType>::operator=( const Array &right ) {

  if ( &right != this ) {  // check for self-assignment
    // for arrays of different sizes, deallocate original
    // left side array, then allocate new left side array.

    if ( capacity != right.capacity ) {
       delete [] ptr;                // reclaim space
       capacity=right.capacity;      // resize this object
       numUsed = right.numUsed;      // reset the numUsed
       ptr = new dataType[right.capacity]; // create space for array copy
       assert( ptr != 0 );           // terminate if not allocated
    }

    for ( int i = 0; i < right.capacity; ++i ){
      ptr[ i ] = right.ptr[ i ];  // copy array into object
      numUsed++;
    }
  }
  return *this;   // enables x = y = z;

} // END of = overload


////////////////////////////////////////////////////////////////////////
//
//   Method name:      [] 
//   Description:      Overloads [] operator for NON CONST arrays
//   Member Type:      Operator Overload
//   Parameters:       int subscript
//   Return Value:     ptr[0]                  
//
////////////////////////////////////////////////////////////////////////

// Overloaded subscript operator for non-const Arrays
// reference return creates an lvalue
template <class dataType> 
dataType &Array<dataType>::operator[](int subscript) {
  // check for subscript out of range error
  assert( subscript >= 0 && subscript < capacity );

  if (subscript > capacity){
     cout << "Error. You are exceeding the array's capacity.";
  }

  if (subscript >= numUsed && capacity > subscript){
    for (int i = 0; i < subscript; i ++){
      numUsed++;
    }
    // numUsed++;
  }

  return ptr[subscript];
} // END of [] overload (non const)

////////////////////////////////////////////////////////////////////////
//
//   Method name:      []                 
//   Description:      Overloads [] operator for CONST arrays
//   Member Type:      Operator Overload
//   Parameters:       int subscript
//   Return Value:     ptr[0]
//
////////////////////////////////////////////////////////////////////////


// Overloaded subscript operator for const Arrays
// const reference return creates an rvalue
// subscript must be in range of "used" elements
template <class dataType> 
const dataType &Array<dataType>::operator[](int subscript) const {
  // check for subscript out of range error

  if (subscript > capacity){
     cout << "Error. You are exceeding the array's capacity.";
  }
  
  if (subscript > numUsed){
    cout << "Error. Your subscript is out of range of useable elements in the array.";
  }

  return ptr[subscript];
} // END of [] overload (const)


////////////////////////////////////////////////////////////////////////
//
//   Method name:      *                 
//   Description:      Overloads * operator
//   Member Type:      Operator Overload
//   Parameters:       none
//   Return Value:     ptr[0]
//
////////////////////////////////////////////////////////////////////////

// dereference operator (return first array value)
template <class dataType> 
dataType Array<dataType>::operator*() const {

  // return dataType();
  return ptr[0];
} // END of *


////////////////////////////////////////////////////////////////////////
//
//   Method name:      +=                 
//   Description:      Overloads += operation
//   Member Type:      Operator Overload
//   Parameters:       dataType elt
//   Return Value:     *this
//
////////////////////////////////////////////////////////////////////////

// Append element to end of array
template <class dataType> 
Array<dataType> &Array<dataType>::operator+=(dataType elt) {
    if (numUsed == capacity){
    dataType *temp=new dataType[capacity+1];
    for (int i = 0; i < capacity; ++i) temp[i]=ptr[i];
    temp[capacity++]= elt;
    delete[] ptr;
    ptr=temp;
    numUsed++;
  }
  else{        // else, numUsed is LESS than the capacity 
    ptr[numUsed++] = elt;
  }
  return (*this);
} // END of +=


////////////////////////////////////////////////////////////////////////
//
//   Method name:      ++                 
//   Description:      Overloads ++ for pre-increment situations
//   Member Type:      Operator Overload
//   Parameters:       none
//   Return Value:     *this
//
////////////////////////////////////////////////////////////////////////

// preincrement - add default element to the front of array
template <class dataType> 
Array<dataType> &Array<dataType>::operator++() {

  dataType *temp=new dataType[capacity+1];
  numUsed++;
  temp[0] = dataType();
  for (int i = 0; i < capacity; ++i) temp[i+1]=ptr[i];
  temp[capacity++]= dataType();
  delete[] ptr;
  ptr=temp;
 
  return(*this);
} // END of++

////////////////////////////////////////////////////////////////////////
//
//   Method name:      ++                 
//   Description:      Overloads ++ for post-increment situations
//   Member Type:      Operator Overload
//   Parameters:       none
//   Return Value:     *this
//
////////////////////////////////////////////////////////////////////////

// postincrement - add default element to the front of array
template <class dataType> 
Array<dataType> Array<dataType>::operator++(int) {
  Array Answ = *this;    
  dataType *temp=new dataType[capacity+1];
  numUsed++;
  temp[0] = dataType();
  for (int i = 0; i < numUsed; i++) temp[i+1]=ptr[i];
  temp[capacity++]= dataType();
  delete[] ptr;
  ptr=temp;
 
  return(Answ);
} // END of ++


////////////////////////////////////////////////////////////////////////
//
//   Method name:      ==                 
//   Description:      Overloads == operator
//   Member Type:      Operator Overload
//   Parameters:       const Array &right 
//   Return Value:     a bool
//
////////////////////////////////////////////////////////////////////////

// Determine if two arrays are equal and
// return true, otherwise return false.
template <class dataType>
bool Array<dataType>::operator==(const Array &right) const {

  return ptr == &right;

} // END of ==


////////////////////////////////////////////////////////////////////////
//
//   Method name:      >                 
//   Description:      Overloads > operator 
//   Member Type:      Operator Overload
//   Parameters:       const Array &right
//   Return Value:     a bool
//
////////////////////////////////////////////////////////////////////////

// Determine which is greater (just compare the number used)
template <class dataType>
bool Array<dataType>::operator>(const Array &right) const  {
 
  return right.getNumUsed() < numUsed;  
} // END of >


////////////////////////////////////////////////////////////////////////
//
//   Method name:      <<             
//   Description:      Overloads << operator
//   Member Type:      Operator Overload
//   Parameters:       ostream &output, const Array<dataType> &A
//   Return Value:     output
//
////////////////////////////////////////////////////////////////////////

// Overloaded output operator for class Array 
template <class dataType> 
ostream &operator<<(ostream &output, const Array<dataType> &A) {
  int i;
  output << "[ ";
  for ( i = 0; i < A.getNumUsed(); i++ ) {
     if (i != 0) { output << ", "; }
     output << A[ i ]; 
  }
  output << " ]" << endl;;

  return output;   // enables cout << x << y;
} // END of <<


////////////////////////////////////////////////////////////////////////
//
//   Method name:      >>               
//   Description:      Overloads >> operator
//   Member Type:      Operator Overload
//   Parameters:       istream &input, Array<dataType> &A
//   Return Value:     input
//
////////////////////////////////////////////////////////////////////////

// Overloaded input operator for class Array 
template <class dataType> 
istream &operator>>(istream &input, Array<dataType> &A) {
  dataType r;
  input >> r;
  A += r;
  return input;   // enables cin >> x >> y;
} // END of >>

#endif

