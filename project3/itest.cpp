#include <iostream>
#include <iomanip>
#include <string>
#include "Array.h"

using namespace std;

template <typename dataType> 
void printArray(const Array<dataType> &);

////////////////////////////////////////////////////////////////////////
//
//   Function name:    main     
//   Description:      creates empty Array object and outputs             
//                     useful data to user                    
//   Parameters:       none                                 
//                                                                 
//   Return Value:     0                             
//
////////////////////////////////////////////////////////////////////////

int main()
{ 
  int array[]= { 1, 2, 3, 4 };
  cout << boolalpha; // for boolean testing

  ///////////////////////////////////
  // create an empty Array object 
  Array<int> iList1;
  cout << "Default Constructor" << endl;
  // output empty object 
  printArray(iList1);

  // array constructor 
  cout << "Constructor from array:" << endl;
  Array<int> iList2(array, 6, 4);
  printArray(iList2);

  // ADD THIS TEST !!!!!!
  // copy constructor 
  // 1) Use the copy constructor make a new Array object
  //    Array object named iList3 as a copy of iList2
  // 2) Use printArray() to print out iList3

  Array<int> iList3(iList2);
  cout << "Copy Constructor:" << endl;
  printArray(iList3);

  // test += on object that is not at capacity
  cout << "Add an item (+= under capacity)" << endl;
  iList1+= 2;
  printArray(iList1);

  // test += on object that is at capacity
  cout << "Add an item (+= at capacity)" << endl;
  iList2+= 20;
  printArray(iList2);

  // change the first value in iList1 to 6
  cout << "Test non-const [] operator (< numUsed)" << endl;
  iList1[0]= 6;
  // Output the Array.
  printArray(iList1);

  // change the third value in iList1 to 7
  cout << "Test non-const [] operator (> numUsed)" << endl;
  iList1[2]= 7;
  // Output the Array.
  printArray(iList1);

  // test ++ : add empty item to iList1
  cout << "Add empty item using preincrement" << endl;
  printArray(++iList2);
  printArray(iList2);

  // test ++ : add empty item to iList1
  cout << "Add empty item using postincrement" << endl;
  printArray(iList2++);
  printArray(iList2);

  // ADD THIS TEST !!!!!!
  // test the assignment operator
  // 1) create a new Array object named iList4
  // 2) use the assignment operator ro set it equal to iList1
  // 3) use printArray() to print out iList4

  Array<int> iList4;
  iList4 = iList1;
  cout << "Assignment:" << endl;
  printArray(iList4);

  // test greater than
  cout << "Test > operator:" << endl;
  cout << "  iList1 > iList1: " << (iList2 > iList1) << endl;
  cout << endl << endl;
  
  // dereference operator
  cout << "Test dereference operator" << endl;
  cout << "  *iList1: " << *iList1 << endl;
  cout << endl;

  return(0);
} // END of main()

////////////////////////////////////////////////////////////////////////
//
//   Function name:    printArray   
//   Description:      simply displays contents of array onto the             
//                     screen for the user
//   Parameters:       const Array<dataType> &MyArray                              
//                                                                 
//   Return Value:     void                             
//
////////////////////////////////////////////////////////////////////////


template <typename dataType> 
void printArray(const Array<dataType> &MyArray) { 
  cout << "  Capacity: " << MyArray.getCapacity() 
       << ", Elements in Use: " << MyArray.getNumUsed() << endl;
  cout << "  Contents: " << MyArray << endl;
  cout << endl;

} // END of printArray()

