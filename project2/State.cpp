#include "State.h"
// State.cpp, our member function implementation for our State class!


// State constructor
State::State(string s, float p, float a){
  name = s;
  population = p;
  area = a;
  }



// we need setters: for the name, population, and area of a state

/*************************************************************************/
/*                                                                       */
/*   Function name:  setName                                             */
/*   Description:    allows us to set a state name               	 */
/*   Parameters:     a string                                            */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/

void State::setName(string s){
    name = s;
} // END of setName()


/*************************************************************************/
/*                                                                       */
/*   Function name:  setPopulation                                       */
/*   Description:    allows us to set a population number             	 */
/*   Parameters:     a float                                             */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/

void State::setPopulation(float p){
  population = p;
} // END of setPopulation()


/*************************************************************************/
/*                                                                       */
/*   Function name:  setArea                                             */
/*   Description:    allows us to set a area number                 	 */
/*   Parameters:     a float                                             */
/*                                                                       */
/*                                                                       */
/* Return Value: void                                                    */
/*                                                                       */
/*************************************************************************/

void State:: setArea(float a){
  area = a;
} // END of setArea()



// and now for getters...


/*************************************************************************/
/*                                                                       */
/*   Function name:  getName                                             */
/*   Description:    allows us to get a specific state name            	 */
/*   Parameters:     none                                                */
/*                                                                       */
/*                                                                       */
/* Return Value: a string                                                */
/*                                                                       */
/*************************************************************************/

string State::getName() const {
  return name;
} // END of getName()


/*************************************************************************/
/*                                                                       */
/*   Function name:  getPopulation                                       */
/*   Description:    allows us to get a specific population number       */
/*   Parameters:     none                                                */
/*                                                                       */
/*                                                                       */
/* Return Value: a float                                                 */
/*                                                                       */
/*************************************************************************/

float State::getPopulation() const {
  return population;
} // END of getPopulation()


/*************************************************************************/
/*                                                                       */
/*   Function name:  getArea                                             */
/*   Description:    allows us to get a specific area number             */
/*   Parameters:     none                                                */
/*                                                                       */
/*                                                                       */
/* Return Value: a float                                                 */
/*                                                                       */
/*************************************************************************/

float State::getArea() const {
  return area;
} // END of getArea()


/*************************************************************************/
/*                                                                       */
/*   Function name:  getPopulationDensity                                */
/*   Description:    allows us to get a specific population density      */
/*   Parameters:     none                                                */
/*                                                                       */
/*                                                                       */
/* Return Value: a float                                                 */
/*                                                                       */
/*************************************************************************/

float State::getPopulationDensity() const {
// getPopulationDensity will calculate the population density then return it

  return population / area * 1000;
} // END of getPopulationDensity


/*************************************************************************/
/*                                                                       */
/*   Function name:  >                                                   */
/*   Description:    operator overload to compare population densities	 */
/*   Parameters:     const State & state                                 */
/*                                                                       */
/*                                                                       */
/* Return Value: a bool                                                  */
/*                                                                       */
/*************************************************************************/

bool State::operator>(const State & state) const{
  return getPopulationDensity() > state.getPopulationDensity();
} 


/*************************************************************************/
/*                                                                       */
/*   Function name:  <                                                   */
/*   Description:    operator overload to compare state names            */
/*   Parameters:     const State & state                                 */
/*                                                                       */
/*                                                                       */
/* Return Value: a bool                                                  */
/*                                                                       */
/*************************************************************************/

bool State::operator<(const State & state) const{
  return name < state.getName();
}
