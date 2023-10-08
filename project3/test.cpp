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
  ///////////////////////////////////
  // 1: create an empty Array object 
  //    using a default constructor

  Array<int> ints(3);
  cout << "Default Constructor" << endl;
  printArray(ints);
  // 2: output the empty object !!!

  // 3: test >> : add an item using >>
  cout << "Add 3 items using input stream: " << endl;
  for (int i = 0; i < 3; i++){
  cin >> ints;
  }
 
  // 4: output final object
  printArray(ints);
  return(0);
} // END of main()

////////////////////////////////////////////////////////////////////////
//
//   Function name:    printArray     
//   Description:      simply displays contents of array to user             
//                                         
//   Parameters:       const Array<dataType> &MyArray                                 
//                                                                 
//   Return Value:     void                             
//
////////////////////////////////////////////////////////////////////////

template <typename dataType> 
void printArray(const Array<dataType> &MyArray) { 
  cout << endl;
  cout << "Array Info:" << endl;
  cout << "  Capacity: " << MyArray.getCapacity() 
       << ", Elements in Use: " << MyArray.getNumUsed() << endl;
  cout << "  Contents: " << MyArray << endl;
  cout << endl;
} // END of printArray()

