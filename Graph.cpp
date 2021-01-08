#include "Graph.h"

Graph:: Graph ()
{
    myGraph.clear();
}


Graph:: Graph (const Graph& other)
{
    myGraph=other.myGraph;
}


Graph::  Graph (std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > otherMap, int otherVertices, int otherEdges)
{
    myGraph=otherMap;
}


Graph& Graph:: operator= (const Graph& other)
{
    if(this!=&other)
    {
        myGraph=other.myGraph;
    }
    return *this;
}


bool Graph:: existsVertex (const std::string vertexName)
{
    if(myGraph.find(vertexName)!=myGraph.end()) return true;
    else return false;
} 


bool Graph:: pathAdjuscent (const std::string& firstVertex, const std::string& secondVertex)
{
    if(existsVertex(firstVertex) && existsVertex(secondVertex))
    {
        std::list<std::pair<std::string, int>> l = myGraph.at(firstVertex);
        for (auto const& i : l) 
        {
            if(i.first==secondVertex) return true;
        }
    }
    return false;
}


void Graph:: addEdge(const std::string& firstVertex, const std::string& secondVertex, int distance)
{
    if(!pathAdjuscent (firstVertex, secondVertex))
    {
        myGraph[firstVertex].push_back(std::make_pair(secondVertex, distance));
    }
}


void Graph:: addVertex (std::string newName, std::list<std:: pair<std::string, int>> l)
{
    if(!existsVertex(newName))
    {
        myGraph.insert(std::make_pair(newName, l));
    }
}


void Graph:: removeEdge (const std::string& firstVertex, const std::string& secondVertex)
{
    if(!existsVertex(firstVertex) || !existsVertex(secondVertex))
    {
        return;
    }
    if(!pathAdjuscent (firstVertex, secondVertex))
    {
        return;
    }
    else
    {
        for(std::list<std::pair<std::string, int>>::iterator i=myGraph[firstVertex].begin(); i!=myGraph[firstVertex].end(); i++)
        {
            std::pair<std::string, int> p=*i;
            if(p.first==secondVertex)
            {
                myGraph[firstVertex].erase(i);
                return;
            }
        }
    }    
}


void Graph:: removeVertex (const std::string& vertexName)
{
    if(!existsVertex(vertexName))
    {
        return;
    }
    myGraph.erase(vertexName);
    for(auto const& i: myGraph)
    {
        for(std::list<std::pair<std::string, int>>::iterator j=myGraph[i.first].begin(); j!=myGraph[i.first].end(); j++)
        {
            std::pair<std::string, int> p=*j;
            if(p.first==vertexName)
            {
                myGraph[i.first].erase(j);
            }
        }
    }
    return;
}


void Graph:: print () const
{
    for (auto const& i : myGraph) {
		std::string Node = i.first;
		std::list<std::pair < std::string, int> > otherNodes = i.second; 
		
		std::cout << Node << "  ->  ";
		for (auto const& j : otherNodes) {
			std::string nameNode = j.first;
			int distance = j.second;
			std::cout << nameNode << " " << distance;
            if(j.first!=otherNodes.back().first) std::cout<<" , ";
		}
		std::cout << std::endl;
	}
}


int Graph:: getDistanceConnectedNodes (const std::string& firstVertex, const std::string& secondVertex)
{
    if(!pathAdjuscent (firstVertex, secondVertex))
    {
        return 0;
    }
    for (auto const& i: myGraph[firstVertex])
    {
        if (i.first==secondVertex) return i.second;
    }
}


std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > Graph:: getMyGraph()
{
    return myGraph;
}
