#pragma once
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
    private:
    
    std::unordered_map<std::string, std:: list<std::pair<std::string, int>>> myGraph;

    public:

    Graph ();
    Graph (const Graph& other);
    Graph& operator= (const Graph& other);

    void print () const;
    bool pathAdjuscent (const std::string& firstVertex, const std::string& secondVertex);
    bool existsVertex (const std::string& vertexName);
    void addEdge (const std::string& firstVertex, const std::string& secondVertex, int distance);
    void addVertex (std::string newName, std::list<std:: pair<std::string, int>>);
    void removeEdge (const std::string& firstVertex, const std::string& secondVertex);
    void removeVertex (const std::string& vertexName);
    int getDistanceConnectedNodes (const std::string& firstVertex, const std::string& secondVertex);
    std::unordered_map<std::string, std:: list<std:: pair<std::string, int>>> getMyGraph() const;

};

#endif
