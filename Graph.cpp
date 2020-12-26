#include "Graph.h"

Graph:: Graph ()
{
    numberOfEdges=0;
    numberOfVerices=0;
    myGraph.clear();
}


Graph:: Graph (const Graph& other)
{
    numberOfVerices=other.numberOfVerices;
    numberOfEdges=other.numberOfEdges;
    myGraph=other.myGraph;
}

Graph::  Graph (std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > otherMap, int otherVertices, int otherEdges)
{
    myGraph=otherMap;
    numberOfVerices=otherVertices;
    numberOfEdges=otherEdges;
}

Graph& Graph:: operator= (const Graph& other)
{
    if(this!=&other)
    {
        numberOfVerices=other.numberOfVerices;
        numberOfEdges=other.numberOfEdges;
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
        ++numberOfEdges;
    }
    else
    {
        //std::cout<<"There already exists a path between these vertices";
    }
}

void Graph:: addVertex (std::string newName, std::list<std:: pair<std::string, int>> l)
{
    if(!existsVertex(newName))
    {
        myGraph.insert(std::make_pair(newName, l));
        ++numberOfVerices;
    }
    else
    {
        // std::cout<<"There already exists such a vertex";
    }
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

std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > Graph:: getMyGraph()
{
    return myGraph;
}
