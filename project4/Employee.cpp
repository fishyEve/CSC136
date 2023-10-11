#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include "Employee.h"

using namespace std;

/************************************************************/
/*  Author:    	       	    Eve	Collier
/*  Course:    	       	    CSC	136
/*  Professor Name:    	    Carelli
/*  Assignment:        	    Project 4
/*  Filename:         	    Employee.cpp
/*
/*
/************************************************************/

// copy constructor
Employee::Employee(const Employee& E) { 
  name= E.name;
  numSales= E.numSales;
  sales= NULL;
  if(E.sales) {
    sales=new float[numSales];
    for(int i=0; i<numSales; i++) { sales[i]= E.sales[i]; }
  }
} // END of copy constructor


// destructor
Employee::~Employee() { 
  delete[] sales;
} // END of destructor


// delete existing information
void Employee::clear() { 
  name=""; numSales=0; 
  if(sales) delete[] sales;
  sales= NULL; 
} // END of clear()


// Overloaded subscript operator 
// const reference return creates an rvalue
const float Employee::operator[](int subscript) const {
  // check for subscript out of range error
  assert( subscript >= 0 && subscript < numSales );

  return sales[ subscript ]; // const reference return
} // END of [] overload


// Overloaded assignment operator
Employee &Employee::operator=( const Employee &right )
{
 if ( &right != this ) {  // check for self-assignment
    
  name= right.name;       // copy the name

  // for arrays of different sizes, deallocate original
  // left side array, then allocate new left side array.
  if ( numSales != right.numSales ) {
    delete [] sales;               // reclaim space
    numSales = right.numSales;     // renumSales this object
    sales = new float[ numSales ]; // create space for array copy
    assert( sales != 0 );          // terminate if not allocated
  }

  for ( int i = 0; i < numSales; i++ )
    sales[ i ] = right.sales[ i ];  // copy array into object
  }

 return *this;   // enables x = y = z;
} // END of = overload


// Append element to end of array
Employee &Employee::operator+=(float value) {
  float *temp=new float[numSales+1];
  for(int i=0; i<numSales; i++) { temp[i]= sales[i]; }
  temp[numSales++]=value;
  delete[] sales;
  sales=temp;
  return(*this);
} // END of += overload


// Output an Employee
ostream& operator<<(ostream &os, const Employee &E) {
  os << left << setw(12) << E.getName();
  os << fixed << setprecision(2);
  os << right << " " << setw(5) << E.getTotal() << " : ";

  for(int i=0; i<E.getNumSales(); i++) {
    os << "  " << right << setw(5) << E[i];
  }
  os << endl;
  return os;
} // END of << overload


// input an Employee
ifstream& operator>>(ifstream &ifs, Employee &E) {
  string line;

  if(getline(ifs,line)) {
    E.clear(); // remove existing information

    stringstream ss(line);
    string name; float value;
    ss >> name;
    E.setName(name); 

    while(ss >> value) {
      E+= value;
    }
  }
  return ifs;
} // END of >> overload


//////////////////////////////////////////
// Complete the following
//////////////////////////////////////////

// the above code was PROVIDED by Carelli. Everything below was written by Eve :)

/************************************************************/
/*  Function name:          getTotal()
/*  Description:            adds up all sales and returns total
/*
/*  Parameters:             none
/*
/*  Return value:           float         
/*
/*
/************************************************************/
float Employee::getTotal() const {
  float total = 0;
  // if the list is empty, set the sales equal to 0
  if (sales == NULL){
    total = 0;
    return total;
  }

  for (int i = 0; i < numSales; i++){
    total += sales[i];    // loop through sales and add all totals
  }

  return total;   
} // END of getTotal()


/************************************************************/
/*  Function name:          == overload
/*  Description:            determines if two names are equal
/*                          then returns true or false
/*  Parameters:             const Employee &E
/*
/*  Return value:           bool         
/*
/*
/************************************************************/
bool Employee::operator==(const Employee &E) {
  return name == E.getName();
} // END of == overload

/************************************************************/
/*  Function name:          <= overload   
/*  Description:            compares sales totals
/*     	       	       	   
/*  Parameters:             const Employee &E         
/*
/*  Return value:           bool 
/*
/*
/************************************************************/
bool Employee::operator<=(const Employee &E) {
  if (getTotal() > E.getTotal()){
     return false;
  }

  else{
  return true; 
 } 
} // END of <= overload

/************************************************************/
/*  Function name:          >= overload
/*  Description:            compares employee names             
/*                                                    
/*  Parameters:             const Employee &E
/*
/*  Return value:           bool
/*
/*
/************************************************************/
bool Employee::operator>=(const Employee &E) {

  if (getName() >= E.getName()){
    return true;
  }
  else{
    return false;
  }
  
} // END of >= overload
