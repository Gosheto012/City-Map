#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#include"Data.h"
#include<cstring>
#include<queue>
#include<stack>


class Algorithms
{
    Data loadedGraph;
    std::string fileName;

    public:
    
    Algorithms (std::string b);
    bool isReachable(std::string start, std::string finish); //1

    bool canReturnToSamePlace (std::string start); //4 

    bool canReachAllOthers (std::string start); // 6

  
    bool stringsBelongInArray (std::string str, std::vector<std::string> strArray);

    bool isNoWayCrossroad (std::string start);//
    void printOneWayStreets ();//7


    void traverse (std::string name, std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > map, std::unordered_map<std::string, bool>& m);
    bool isConnected ();
    bool samePowerEachEdge (); //5
    void printEulerianPathIfAvailable (); //5 Hierholzer's algorithm 

    void Diikstra (std::string start, std:: string finish);
    Data getData ();
};

#endif
