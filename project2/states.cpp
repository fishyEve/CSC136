#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include "State.h"

// DO NOT CHANGE THIS VALUE!
#define ARRAYSIZE 8


/************************************************************/
/* Author:                Eve Collier                       */
/* Creation Date:         September 29, 2022                */
/* Due Date:              October 6, 2022                   */
/* Course:                CSC 136 010                       */
/* Professor Name:        Dr John Carelli                   */
/* Assignment:            Project 2, States                 */
/* Filename:              states.cpp                        */
/* Purpose:               A continuation of Project 1       */
/*                        except now we are working with    */
/*                        a State class                     */
/*                                                          */
/*                                                          */
/*                                                          */
/*                                                          */
/************************************************************/


// read the data file, store in class
int readDatafile(State[], int&);
// output the formatted "raw data"
void outputData(State[], int);
// output the sorted data, including population density
void outputSorted(State[], int );

// sorting routines - use a bubble sort
void sortAscend(State[], int);  // set this up to sort by name
void sortDescend(State[], int); // set this up to sort by population density
void swap(State[], int);        // used by the bubble sort


/*************************************************************************/
/*                                                                       */
/*   Function name:  main                                                */
/*   Description:    we call all functions here to execute program       */
/*   Parameters:     none                                                */
/*                                                                       */
/*                                                                       */
/* Return Value: int                                                     */
/*                                                                       */                            
/*************************************************************************/
int main() {
  // main() will basically be where we call each function in the order that 
  // everything needs to execute.

  State slist[ARRAYSIZE];
  int max;      // num of lines in file

  cout << setprecision(1);  // decimal point is set to 1
  cout << fixed;            // to make sure .0 shows up if num has no decimal
  

  readDatafile(slist, max);

  //if max num hasn't been incremented, it means we ran into a problem and we need to exit the program
  if (max == 0){
    return 1;
  }

  // if we got to this point...we are good to go!
  outputData(slist, max);
  sortAscend(slist, max);
  outputSorted(slist, max);
  sortDescend(slist,max);
  outputSorted(slist, max);  

  return 0;
} // END of main()



/*************************************************************************/
/*                                                                       */
/*   Function name:  readDatafile                                        */
/*   Description:    user enters data file and the program reads it      */
/*   Parameters:     State[] and int                                     */
/*                                                                       */
/*                                                                       */
/* Return Value: int                                                     */
/*                                                                       */                            
/*************************************************************************/
int readDatafile(State s[], int &max){
  // We need to read the data file that we prompt the user to enter

  string fname;   // this will be the file we are reading 
  ifstream ifs;  // and this is needed for reading/opening the file
   
  string state; // state name
  float pop;    // population
  float area;   // area


  // prompt the user to enter a file name
  cout << "Enter file name: ";
  cin >> fname;

  // next we need to make sure that the file can be opened
  ifs.open(fname);

  // if the file CANNOT open...
  if (ifs.fail()){
    cout << "There was an error opening the file: " << fname << ". Maybe you entered it wrong? Please try again." << endl;
    return 1; // there was an error, so we told the user and are now exiting gracefully
  }

  // if we get to this point, the file was opened successfully!
 
  // now we need to loop through the file
  for (max = 0; max < ARRAYSIZE && !ifs.eof(); max++){
    // now we need to insert the information from the file into our State array

    ifs >> state;             // state name
    s[max].setName(state);
    
    ifs >> pop;               // state population
    s[max].setPopulation(pop);
   
    ifs >> area;              // state area
    s[max].setArea(area);

    // IF we reach the end of the file, we need to STOP this loop    
    if (ifs.eof()){
      return 0;
    }   
  
  }

  return 0;
} // END of readDatafile()


/*************************************************************************/
/*                                                                       */
/*   Function name:  outputData                                          */
/*   Description:    simply displaying raw data onto the screen 	 */
/*   Parameters:     State[] and int                                     */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/
void outputData(State s[], int max){

  // first line prints the introduction info
  cout << endl;
  cout << "State data:" << endl;
  cout << "--------" << endl;

  // now we simply loop through the contents of our State array and print the data
  for (int i = 0; i < max; i++){
    cout << left << setw(14) << s[i].getName();        // print state name
    cout << right << setw(7) << s[i].getPopulation();  // print population
    cout << right << setw(7) << s[i].getArea();        // print area
    cout << endl;                                      // and print an extra line for neatness
  }


} // END of outputData()

/*************************************************************************/
/*                                                                       */
/*   Function name:  outputSorted                                        */
/*   Description:    simply displaying sorted data onto the screen       */
/*   Parameters:     State[] and int                                     */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/
void outputSorted(State s[], int max){

  // FIRSTLY we need to display the top portion of the menu
  cout << endl;
  cout << "Sorted States:" << endl;
  cout << "--------" << endl;

  // now we can loop through the file and print all of the data

  for (int i = 0; i < max; i++){
    cout << left << setw(14) << s[i].getName();              // print state name
    cout << right << setw(7) << s[i].getPopulationDensity(); // print population density
    cout << right << setw(7) << s[i].getPopulation();        // print population
    cout << right << setw(7) << s[i].getArea();              // print area
    cout << endl;                                            // and an extra line for neatness
  }

} // END of outputSorted()



/*************************************************************************/
/*                                                                       */
/*   Function name:  sortAscend                                          */
/*   Description:    bubble sort method in ASCENDING order      	 */
/*   Parameters:     State[] and int                                     */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/
void sortAscend(State s[], int max){
  // this function sorts state names by ASCENDING alphabetical order
  
  // firstly we need to initalize a flag
  
  bool flag = true;

  for (int i = 0; i < max && flag; i++){
    // flag must be set to false so that we only enter this loop IF its true
    flag = false;
    for (int j = 0; j < max-1; j++){
      // IF the first letter of the word to the right is smaller...we swap
      if (s[j+1].getName() < s[j].getName()){
        // If we get to this point, we need to call our swap AND set flag to true
        swap(s[j], s[j+1]);
        flag = true;
      }    

    }
  }

} // END of sortAscend()


/*************************************************************************/
/*                                                                       */
/*   Function name:  sortDescend                                         */
/*   Description:    bubble sort method in DESCENDING order              */
/*   Parameters:     State[] and int                                     */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/
void sortDescend(State s[], int max){
  // Here is where we'll use a bubble sort method to organize a state's population density in DESCENDING order

  // firstly, we need to initalize a flag

  bool flag = true;

  for (int i = 0; i < max && flag; i++){
    // flag must be set to false so that we only enter this loop IF its true
    flag = false;

    for (int j = 0; j < max-1; j++){
      // IF the number to the right of our current number is larger...we swap
      if (s[j+1].getPopulationDensity() > s[j].getPopulationDensity()){
        // we need to call our swap method since we ended up here
        swap (s[j], s[j+1]);
       // And since a swap occured, our flag can be set back to true
       flag = true;
      }
    }
  }

} // END of sortDescend()


/*************************************************************************/
/*                                                                       */
/*   Function name:  swap                                                */
/*   Description:    code to swap two items for bubble sorts             */
/*   Parameters:     State[] and int                                     */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/
void swap (State &a, State &b){
  // Here is where the swap work happens for our bubble sort methods
  State temp = a; a = b; b = temp;  

} // END of swap()
