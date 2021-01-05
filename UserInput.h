#pragma once
#ifndef __UserInput_H
#define __UserInput_H

#include "Algorithms.h"


class UserInput
{
  private:
  
  Algorithms map;

  void cityMenu () const;
	void printCity () const; 
	void isReachable ();
	void threeShortestPaths ();
	void threeAlternativeShortestPaths ();
	void canReturnToSamePlace ();
	void cityTour ();
	void canReachAllOthers ();
	void oneWayStreets ();
	void userInputSingleCrossroad (std::string& vertexName);
	void userInputTwoCrossroads (std::string& start, std::string& finish);
    
	public:

	UserInput (std::string file);
	void run ();


};

#endif
