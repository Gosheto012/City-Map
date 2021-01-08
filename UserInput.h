#pragma once
#ifndef __UserInput_H
#define __UserInput_H

#include "Algorithms.h"


class UserInput
{
	private:
	
    Algorithms map;
	std::string location;
	std::list<std::string> closedCrossroads;
	std::unordered_map<std::string, std::list<std::pair<std::string, int>>> vertexSave;


    void cityMenu () const;
	void printCity () const;
	void isReachable ();
	void threeShortestPaths ();
	void threeAlternativeShortestPaths ();
	void canReturnToSamePlace ();
	void cityTour ();
	void canReachAllOthers ();
	void oneWayStreets ();

	void interactiveMenu () const;
	void startLocation ();
	void changeLocation ();
	void printNeighbours ();
	void move();
	void addClosedCrossroad ();
	void openCrossroad();
	void printClosedCrossroads ();
	void interactiveTour ();


	bool isClosed (std::string vertexName);
	void closeGraph(Graph& graph);


	void userInputSingleCrossroad (std::string& vertexName);
	void userInputTwoCrossroads (std::string& start, std::string& finish);

	void interactive ();
    
	public:

	UserInput (std::string file);
	void run ();
};

#endif
