#include"Data.h"

Data:: Data ()
{
    Graph graph;
}


int Data:: numberVertexesInLine (std::string line) // including the vertex
{
    int currentWordNumber=0;
    for(int i=0;i<=line.length();i++)
    {
        if(line[i]==' ')
        {
            currentWordNumber++;
        }
    }
    return currentWordNumber/2+1;
}


std::string Data:: extractNameGraph(std::string line, int wordNumber) // mai zapochva broene ot 1
{
    std::string tempString;
    int currentWordNumber=0;
    for(size_t i=0;i<line.length();i++)
    {
        if(line[i]==' ' || i==line.length()-1) // da go vidq utre
        {
            if(i==line.length()-1) tempString+=line[i];
            currentWordNumber++;
            if (wordNumber==currentWordNumber)
            {
                return tempString;
            }
            tempString="";
        }
        else
        {
            tempString+=line[i];
        }
    }
    return "";
}


std::list<std::pair<std::string, int>> Data:: makeListFromLine (std::string line)//sh proam posle da ne vikamm gornata funkciq za po malka slojnost
{
    std::list<std::pair<std::string, int>> result;
    int counter=1;
    int index=2;
    while (counter<numberVertexesInLine(line))
    {
        std::string currentName= extractNameGraph(line, index);
        int currentDistance = stoi(extractNameGraph(line, index+1));
        std:: pair<std::string, int> currentPair;
        currentPair.first=currentName;
        currentPair.second=currentDistance;
        result.push_back(currentPair);
        index+=2;
        ++counter;
    }
    return result;
}


void Data:: loadDataFromFile (const char *fileName) // proverka da napraq dali ima dr rebra
{
    std:: ifstream file;
    std::string line;
    file.open (fileName);
    while (getline(file, line))
    {
        std::list<std::pair<std::string, int>> currentList = makeListFromLine(line);
        std::string currentVertex =extractNameGraph(line, 1);
        graph.addVertex(currentVertex, currentList);
    }
     file.close();
}



void Data:: printGraph () const
{
    graph.print();
}

Graph Data:: getGraph ()
{
    return graph;
}
