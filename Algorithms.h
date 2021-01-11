#pragma once
#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#include"Data.h"
#include<cstring>
#include<queue>
#include<stack>
#include<map>
#include<limits>

class Algorithms
{
    private:

    Data loadedGraph;

    public:
    
    //tasks 1, 4, 6, 7
    void loadData (const std::string& file);
    bool existsVertex (const std::string& vertexName);
    bool isReachable(const std::string& start, const std::string& finish, std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map); 
    bool canReturnToSamePlace (const std::string& start);
    bool canReachAllOthers (const std::string& start); 
    bool isNoWayCrossroad (const std::string& start);
    void printOneWayStreets ();

    //task 5
    void traverse (std::string name, std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map, std::unordered_map<std::string, bool>& m);
    bool isConnected (std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map);
    bool isEmptyCrossroad (const std::string& vertexName,  std::unordered_map<std::string, std:: list<std:: pair<std::string, int>>> map);
    bool allEmptyCrossroads (std::unordered_map<std::string, std:: list<std:: pair<std::string, int>>> map);
    void removeAllEmptyCrossroads (std::unordered_map<std::string, std:: list<std:: pair<std::string, int>>>& map);
    bool samePowerEachEdge (std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map); //5
    void printEulerianPathIfAvailable (std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map, bool flag, std::string location); //5 Hierholzer's algorithm 
                                                                                                            //flag && location for the interactive mode

    //tasks 2, 3
    std::pair<std::vector<std::string>, int> DiikstraReturn (const std::string& start, const std:: string& finish, std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map);
    std::vector<std::pair<std::vector<std::string>, int>> threeShortestPathsHelper (const std::string& start, const std::string& finish, Graph graph);
    std::pair<std::vector<std::string>, int>  addCostToListandReturnShortest (std::list<std::pair<std::vector<std::string>, int>> B, Graph graph);
    std::list<std::pair<std::string, int>> returnListVertex (const std::string& vertexName,  std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map);

    void addTransitionalEdge (std::list<std::pair<std::string, std::pair<std::string, int>>>& edgesSave, std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map, std::string& name );

    void printThreeShortestPaths (std::vector<std::pair<std::vector<std::string>, int> >& A);
    void threeShortestPaths (const std::string& start, const std::string& finish);
    void threeShortestPathsAfterClosing (const std::string& start, const std::string& finish);

    Data getData () const;
};

#endif
