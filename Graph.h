#ifndef __GRAPH_H
#define __GRAPH_H

#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<unordered_map>
#include<utility>
#include<iterator>

class Graph
{
    int numberOfVerices;
    int numberOfEdges;
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > myGraph;

    public:

    Graph ();
    Graph (const Graph& other);
    Graph (std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > otherMap, int otherVertices, int otherEdges);
    Graph& operator= (const Graph& other);

    void print () const;
    void addEdge (const std::string& firstVertex, const std::string& secondVertex, int distance);
    bool pathAdjuscent (const std::string& firstVertex, const std::string& secondVertex);
    bool existsVertex (const std::string vertexName);
    void addVertex (std::string newName, std::list<std:: pair<std::string, int>>);
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > getMyGraph();
};

#endif
