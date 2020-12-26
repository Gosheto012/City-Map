#ifndef __DATA_H
#define __DATA_H

#include"Graph.h"
#include<sstream>
#include<fstream>


class Data
{
    Graph graph;

    public:


    Data ();
    int numberVertexesInLine (std::string line);
    std::string extractNameGraph(std::string line, int wordNumber);
    std::list<std::pair<std::string, int>> makeListFromLine (std::string line);
    void loadDataFromFile (const char *fileName);
    void printGraph () const;
    Graph getGraph ();
};




#endif
