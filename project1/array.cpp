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
/* Purpose:               Both programs will read info      */
/*                        from a data file, then output a   */
/*                        list with the information sorted  */
/*                        by each state's population- from  */
/*                        highest to lowest                 */
/*                                                          */
/*                                                          */
/************************************************************/

// prototypes
int readDatafile(string[], float[], float[], int&);
void calcPopDensity(float[], float[], float[],  int );
void outputRawData(string[], float[],float[], int );
void outputAllData(string[], float[], float[],float[], int );
void bubbleSort(string n[], float p[], float a[], float pd[], int max);

// a global to help us later
int num;
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
  string names[ARRAYSIZE];        // state names
  float population[ARRAYSIZE];    // state population
  float area[ARRAYSIZE];          // state area (square miles)
  int max;                        // will hold the num of lines in a file  
  float popDensity[ARRAYSIZE];    // state population density
    
 
  cout << setprecision(1);        // set decimal point to 1
  cout << fixed;                  // to make sure .0 shows if there is no decimal

  // At this point, all we need to do is call each written function in the correct
  // order that they need to be executed in

  readDatafile(names, population, area, max);
  // after we read the data file...if any errors occured, num will be 1, which means we need to terminate the program
  if (num == 1){
    return 1;
  }
  // if that statement doesn't execute, the rest of the program can proceed as normal:
  outputRawData(names, population, area, max);
  calcPopDensity(population, area, popDensity, max);
  outputAllData(names, population, area, popDensity, max);
  bubbleSort(names, population, area, popDensity, max);   
  outputAllData(names, population, area, popDensity, max);


  return 0;

} // END of main()


/*************************************************************************/
/*                                                                       */
/*   Function name:  readDatafile                                        */
/*   Description:    opens and reads the datafile                        */
/*   Parameters:     array of string for people, then two float ararys   */
/* for population + area. The max int is established here                */
/*                                                                       */
/* Return Value: int                                                     */ 
/*             	       	       	       	       	       	       	       	 */
/*************************************************************************/

int readDatafile(string n[], float p[], float a[], int &max) {
  string fname;   // our file
  ifstream ifs;   // needed tor reading/ opening the file
     
 
  // Firstly, the user needs to be prompted to enter their datafile name
  cout << "Enter file name: ";
  cin >> fname;


  // We need to make sure the file can be opened
  ifs.open(fname);
  

  // If the file CANNOT be opened...
  if (ifs.fail()){

    cout << "There was an error opening the file: " << fname << ". Maybe you entered it wrong? Please try again." << endl;
    num = 1;
    return 1;                       // IF there is an error, we alert the user and exit gracefully.
  }
  
 // If we've reached this point, it means our file was opened and read successfully!
 

 // Loop through the file
 for (max = 0; max < ARRAYSIZE && ifs >> n[max]; max++){
  // We need to insert each index from the file into the appropriate array
  // the state name was already handled above
  ifs >> p[max];  // the population
  ifs >> a[max];  // the area
  } 

  // IF the max = 0, that means the file was empty!
  if (max == 0){ 
  cout << "The entered file is empty! Did you enter the wrong one? Please try again." << endl;
  num = 1;
  return 1;
  }

  return 0;
} // END of readDatafile()

/*************************************************************************/
/*                                                                       */
/*   Function name:  outputRawData                                       */
/*   Description:    simply displaying data onto the screen              */
/*   Parameters:     array of string values, two float arrays, and       */
/* an int holding the max value                                          */
/*                                                                       */
/* Return Value: void                                                    */
/*             	       	       	       	       	       	       	       	 */
/*************************************************************************/

void outputRawData(string n[], float p[], float a[], int max) {
  
  // FIRST we need to display the fact that this is raw data on the screen
  cout << endl;
  cout << "Raw data: " << endl;
  cout << "--------" <<	endl;

  // Loop through the file and print the data
  for (int i = 0; i < max; i++){
    cout << left << setw(14) << n[i];   // this displays the state 
    cout << right << setw(7) <<  p[i];  // this displays the population
    cout << right << setw(7) <<  a[i];  // and this displays the area
    cout << endl;                       // endl so that the next set of data starts on a new line
  
  }

}// END of outputRawData()


/*************************************************************************/
/*                                                                       */
/*   Function name:  calcPopDensity                                      */
/*   Description:    calculations for population density                 */
/*   Parameters:     two float arrays and a third to store the newly     */
/* calculated info into. Also the max val int                            */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/

void calcPopDensity(float p[], float a[], float pd[], int max) {

  // Loop through the file
  // Save the calculated population density into the pd[] array
  for (int i = 0; i < max; i++){
      pd[i] = p[i] / a[i] * 1000; // multiply by 1000 because the population is millions and area is in thousands
}


} // END of calcPopDensity()

/*************************************************************************/
/*                                                                       */
/*   Function name:  outputAllData                                       */
/*   Description:    simply outputting the data onto the screen          */
/*   Parameters:     array holding names, array holding population       */
/* density, people and area, and the max int                             */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/

void outputAllData(string n[], float p[], float a[], float pd[], int max)  {
  // this will be just like rawdata, except with an extra bit of information
  cout << endl;
  cout << "All data: " << endl;
  cout << "--------" << endl;

  // Loop through the file and print the data
  for (int i = 0; i < max; i++){
    cout << left << setw(14) << n[i];   // this displays the state
    cout << right << setw(7) << pd[i];  // population density
    cout << right << setw(7) <<  p[i];  // population
    cout << right << setw(7) <<  a[i];  // area
    cout << endl;
  }


} // END of outputAllData()

/*************************************************************************/
/*                                                                       */
/*   Function name:  bubbleSort                                          */
/*   Description:    sorting info using bubble method                    */
/*   Parameters:     all 4 arrays and the int holding the max value      */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/

void bubbleSort(string n[], float p[], float a[], float pd[], int max){

  // initalize a flag- will be used to see if a swap happened

  bool flag = true;
  
  // as long as the flag is true and we haven't gone through the max amount of
  // lines in the file..we enter the loop

  for (int i = 0; i < max && flag; i++){
    flag = false; // IF the flag isn't set back to true, it means there was no swap and we're done
    
    // loop through one less than the max to check the number to the right of our current number...
    for (int j = 0; j < max-1; j++){

      if (pd[j+1] > pd[j]) { // if the num to the right is bigger we swap

          string temp = n[j+1]; n[j+1] = n[j]; n[j] = temp;

          float temp1 = pd[j+1]; pd[j+1] = pd[j]; pd[j] = temp1;

          float temp2 = p[j+1]; p[j+1] = p[j]; p[j] = temp2;

          float temp3 = a[j+1]; a[j+1] = a[j]; a[j] = temp3;
         
          flag = true;  // a swap happened so the flag is true
        }

     }
  
 
  }


} // END of bubbleSort()
