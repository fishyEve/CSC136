#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ARRAYSIZE 8

/************************************************************/
/* Author:                Eve Collier                       */
/* Creation Date:         September 6, 2022                 */
/* Due Date:              September 15, 2022                */
/* Course:                CSC 136 010                       */
/* Professor Name:        Dr John Carelli                   */
/* Assignment:            Program 1, States                 */
/* Filename:              array.cpp & struct.cpp            */
/* Purpose:               Both programs will read           */
/*			  informatio on US states from a                    */
/*			  data file, then output a                          */
/*			  formatted list with the                           */
/*			  information sorted by each                        */
/*			  state's  population- from                         */
/*		          highest to lowest                           */
/*                      			                              */ 		
/*							                                            */
/************************************************************/

// struct definition for a state object
struct state {
  string name;         // state name
  float population;    // state population
  float area;          // state area (square miles)
  float popDensity;    // state population density
};                  

// prototypes
int readDatafile(state[], int&);
void calcPopDensity(state[], int);
void outputRawData(state[], int);
void outputAllData(state[], int);
void bubbleSort(state[], int);

// global to help us later
int num;
/*************************************************************************/
/*                                                                       */
/*   Function name:  main                                                */
/*   Description:    we call all functions here to execute program	     */
/*   Parameters:     none                                                */
/*                                                                       */
/*                                                                       */
/* Return Value: int                                                     */
/*                                                                       */
/*************************************************************************/

int main() {  
  // here the struct is called and made
  state slist[ARRAYSIZE];
  int max = 0;
  

  cout << setprecision(1);   // set decimal point to 1
  cout << fixed;             // to make sure .0 shows if the num has no decimal 

  // all we need to do is call the functions in the correct order to run the program

readDatafile(slist, max);
  // after we read the data file, we need to check num. If its 1, there was an error, and we need to temrinate the program
  if (num == 1){
    return 1;
  }
  // If we get to this point, we are good to go and the program can run normally!
  outputRawData(slist, max);
  calcPopDensity(slist, max);
  outputAllData(slist, max);
  bubbleSort(slist, max);
  outputAllData(slist, max);
  
  return 0;

} // END of main()




/*************************************************************************/
/*                                                                       */
/*   Function name:  readDatafile                                        */
/*   Description:    we read the inputted file here                    	 */
/*   Parameters:     struct state and an int holding the max value       */
/*                                                                       */
/*                                                                       */
/* Return Value: int                                                     */
/*                                                                       */
/*************************************************************************/

// open and read the datafile
int readDatafile(state list[], int &max){
  string fname;  // the file 
  ifstream ifs;  // used to read/write/open the file
  

  // firstly we need to prompt the user to enter in the data file we are trying to read
  cout << "Enter file name: ";
  cin >> fname;

  // now we need to open the file
  ifs.open(fname);
  
  // IF the file cannot be opened...
  if (ifs.fail()){
    // We give the user an error message then exit gracefully
    cout << "There was an error opening the file: " << fname << ". Maybe you entered it wrong? Please try again."<< endl;
    num = 1;
    return num; 
  }


  

  // If we've reached this point, the file was open and read successfully!

  // now we need to loop through the file
  for (max = 0; max < ARRAYSIZE; max++){
    // and insert the correct data at the correct spot in the struct
    ifs >> list[max].name;        // state name
    ifs >> list[max].population;  // state population
    ifs >> list[max].area;        // state area
  }

  // IF max = 0, that means the file is empty!
  if (max == 0){
    cout << "The entered file was empty. Did you pick the wrong one or something? Please try again." << endl;
    num = 1;
    return num;
  }

  return num;

} // END of readDatafile()


/*************************************************************************/
/*                                                                       */
/*   Function name:  outputRawData                                       */
/*   Description:    simply displaying data onto the screen              */
/*   Parameters:     struct state and an int holding the max value       */
/*                                               		                     */
/*                                                                       */
/*   Return Value: void        					                                 */
/*           	  					       	                                        */
/*************************************************************************/


void outputRawData(state list[], int max){

  // first print the intro information
  cout << endl;
  cout << "Raw data:" << endl;
  cout << "--------" <<	endl;

  // Now we need to loop through the contents and print the data
  for (int i = 0; i < max; i++){
    cout << left << setw(14) << list[i].name;        // print the state name
    cout << right << setw(7) << list[i].population;  // print the state population
    cout << right << setw(7) << list[i].area;        // print the state area
    cout << endl;				     // and print a new line so everythings all neat

  }

} // END of outputRawData()


/*************************************************************************/
/*                                                                       */
/*   Function name:  calcPopDensity                                      */
/*   Description:    calculations for population density                 */
/*   Parameters:     struct state and an int holding the max value     	 */
/*                                                                       */
/*                                                                       */
/*   Return Value: void                                                  */
/*                                                                       */
/*************************************************************************/

void calcPopDensity(state list[], int max){

// We need to loop through the file
  for(int i = 0; i < max; i++){
    list[i].popDensity = list[i].population / list[i].area * 1000; // multiply by 1000 because the population is in millions and area is in thousands
  }

} // END of calcPopDensity()



/*************************************************************************/
/*                                                                       */
/*   Function name:  outputAllData                                       */
/*   Description:    displaying all data onto the screen                 */
/*   Parameters:     struct state and an int holding the max value	     */
/*                                                                       */
/*                                                                       */
/*   Return Value: void                                                  */
/*                                                                       */
/*************************************************************************/

void outputAllData(state list[], int max){

  // first display the top part of the menu
  cout << endl;
  cout << "All data:" << endl;
  cout << "--------" << endl;

  // Now we loop through the file and print the data
  for (int i = 0; i < max; i++){
  cout << left << setw(14) << list[i].name;
  cout << right << setw(7) << list[i].popDensity;
  cout << right << setw(7) << list[i].population;
  cout << right << setw(7) << list[i].area;
  cout << endl;
  }

} // END of outputAllData()


/*************************************************************************/
/*                                                                       */
/*   Function name:  bubbleSort                                          */
/*   Description:    sorting info using bubble method                    */
/*   Parameters:     struct state and an int holding the max value	     */
/*                                                                       */
/*                                                                       */
/*   Return Value: void                                                  */
/*                                                                       */
/*************************************************************************/

void bubbleSort(state list[], int max){

  // initalize a flag to see when a swap takes place
  bool flag = true;

  for (int i = 0; i < max && flag; i ++){
    // set the flag false so we will ONLY enter this loop again if it becomes true again
    flag = false;    
    
    for (int j = 0; j < max-1; j++){
     
       // IF the number to the right of our current num is bigger, we swap
       if (list[j+1].popDensity > list[j].popDensity){
       
       // If we wind up here, that means a swap needs to happen
       string temp = list[j+1].name; list[j+1].name = list[j].name; list[j].name = temp;
       float temp2 = list[j+1].popDensity; list[j+1].popDensity = list[j].popDensity; list[j].popDensity = temp2;
       float temp3 = list[j+1].population; list[j+1].population = list[j].population; list[j].population = temp3;
       float temp4 = list[j+1].area; list[j+1].area = list[j].area; list[j].area = temp4;
       
       flag = true; // a swap has happened, the flag is true because the loop needs to happen again (unless we are at max-1)
       }
    }
  }

} // END of bubbleSort()

  
