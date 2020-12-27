#include"Algorithms.h"
#define INF 0x3f3f3f3f

Algorithms:: Algorithms (std::string b)
{
    loadedGraph.loadDataFromFile(b.c_str());
}


bool Algorithms:: stringsBelongInArray (std::string str, std::vector<std::string> strArray) // moje da probvam s list
{
    for(size_t i=0; i<strArray.size(); ++i)
    {
        if(strArray[i]==str) return true;
    }
    return false;
}

bool Algorithms:: isReachable (std::string start, std::string finish)
{
    if (!loadedGraph.getGraph().existsVertex(start) || !loadedGraph.getGraph().existsVertex(finish))
    {
        std::cout<<"There is an invalid name among the written above";
        std::cout<<'\n';
        return false;
    }
    if (start==finish) return true;
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::queue<std::string> q;
    std::unordered_map<std::string,  bool> visited;
    q.push(start);
    visited[start]=true;
    while (!q.empty())
    {
        std::string node=q.front();
        q.pop();
        for(auto const& i: map[node])
        {
            if(i.first==finish) return true;
            if(!visited[i.first])
            {
                q.push(i.first);
                visited[i.first]=true;
            }
        }
    }
    return false;
}


bool Algorithms:: canReturnToSamePlace (std::string start)
{
    if (!loadedGraph.getGraph().existsVertex(start))
    {
        std::cout<<"The name of the vertex is invalid\n";
        return false;
    }
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::queue<std::string> q;
    std::unordered_map<std::string,  bool> visited;
    q.push(start);
    while (!q.empty())
    {
        std::string node=q.front();
        q.pop();
        for(auto const& i: map[node])
        {
            if(i.first==start) return true;
            if(!visited[i.first])
            {
                q.push(i.first);
                visited[i.first]=true;
            }
        }
    }
    return false;
}


bool Algorithms:: canReachAllOthers (std::string start)
{
    if (!loadedGraph.getGraph().existsVertex(start))
    {
        std::cout<<"The name of the vertex is invalid\n";
        return false;
    }
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::queue<std::string> q;
    std::unordered_map<std::string,  bool> visited;
    q.push(start);
    visited[start]=true;
    int counter=1;
    int reach = map.size();
    while (!q.empty())
    {
        std::string node=q.front();
        q.pop();
        for(auto const& i: map[node])
        {
            if(counter==reach) return true;
            if(!visited[i.first])
            {
                q.push(i.first);
                visited[i.first]=true;
                ++counter;
            }
        }
    }
    return false;
}

bool Algorithms:: isNoWayCrossroad (std::string start)
{
    if (!loadedGraph.getGraph().existsVertex(start))
    {
        return false;
    }
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    return map[start].empty();
}


void Algorithms:: printOneWayStreets ()
{
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::cout<<"All one-way streets are\n";
    for(auto const& i: map)
    {
        std::string Node = i.first;
        std::list<std::pair < std::string, int> > otherNodes = i.second; 
        for(auto const& j: otherNodes)
        {
            if(isNoWayCrossroad(j.first))
            {
                std::cout<<Node<<" - "<<j.first<<'\n';
            }
        }
    }
}



  bool Algorithms:: samePowerEachEdge ()
{
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::unordered_map<std::string, std::pair<int, int>> result;
    for(auto const& i: map)
    {
        result.insert(std::make_pair(i.first, std::make_pair(i.second.size() ,0)));
    }
    for(auto const& i: map)
    {
        for(auto const& j: i.second)
        {
            result[j.first].second++;
        }
    }
    for(auto const& i: result)
    {
        if(i.second.first!=i.second.second) return false;
    }
    return true;
}


void Algorithms:: traverse (std::string name, std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > map, std::unordered_map<std::string, bool>& m)
{
    m[name]=true;
    std::list<std::pair<std::string, int>> l = map.at(name);
    for (auto const& i: l)
    {
        if (m[i.first]==false) traverse(i.first, map, m);
    }
}


 bool Algorithms:: isConnected ()
 {
    std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::unordered_map<std::string, bool> m;
    for (auto const& i: map)
    {
        m.insert(std::make_pair(i.first, false));
    }
 
    for(auto const& i: map)
    {
        for(auto const& j: m)
        {
            m[j.first]=false;
        }
        traverse(i.first, map, m);
        for(auto const& j: m)
        {
            if(!m[j.first]) return false;
        }
    }
    return true;
 }

void Algorithms:: printEulerianPathIfAvailable ()
{
    if(!samePowerEachEdge() || !isConnected())
    {
        std::cout<<"You cannot cross all the streets without repeating\n";
        return;
    }
    std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::unordered_map<std::string,int> edge_count; 
  
    for (auto const& i: map) 
    { 
        edge_count.insert (std::make_pair(i.first, i.second.size()));
    } 
  
    std::stack<std::string> curr_path; 
  
    std::vector<std::string> circuit; 
   
    curr_path.push(map.begin()->first); 
    std::string curr_v = map.begin()->first; 
    while (!curr_path.empty()) 
    { 
        if (edge_count[curr_v]) 
        { 
            curr_path.push(curr_v); 
   
            auto next_v = map[curr_v].rbegin()->first; 
            edge_count[curr_v]--; 
            map[curr_v].pop_back(); 
  
            curr_v = next_v; 
        } 
  
        else
        { 
            circuit.push_back(curr_v); 
  
            curr_v = curr_path.top(); 
            curr_path.pop(); 
        } 
    } 
    for (int i=circuit.size()-1; i>=0; i--) 
    { 
        std::cout << circuit[i]; 
        if (i) 
           std::cout<<" -> "; 
    } 
}

Data Algorithms:: getData ()
{
    return loadedGraph;
}

void Algorithms:: Diikstra (std::string start, std:: string finish)
{
    if (!loadedGraph.getGraph().existsVertex(start) || !loadedGraph.getGraph().existsVertex(finish))
    {
        std::cout<<"There is an invalid name among the written above";
        std::cout<<'\n';
        return ;
    }
    std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::unordered_map<std::string, int> Q;
    std::map<std::string, std::string> previous;
    for(auto const& i: map)
    {
        Q.insert(std::make_pair(i.first, INF));
    }
    Q[start]=0; 
    std::string currentVertex;
    std::list<std::string> finalNodeSequence;
    while (!Q.empty())
    {
        int min=INF;
        for(auto const& i: Q)
        {
            if(i.second<=min)
            {
                min=i.second;
                currentVertex=i.first;
            }
        }
        int distance = Q[currentVertex];
        Q.erase(currentVertex);
        if(currentVertex==finish)
        {
            if(distance!=INF)
            {
                std::string elementToAdd=finish;
                while(elementToAdd!="")
                {
                    finalNodeSequence.push_front(elementToAdd);
                    elementToAdd=previous[elementToAdd];
                }
                for(std::list<std::string>::iterator i=finalNodeSequence.begin(); i != finalNodeSequence.end(); ++i)
                {
                    std::cout<<*i<<" -> "; 
                }
                std::cout<<distance<<'\n';
                return;
            }
        }
        for (auto const& i: map[currentVertex])
        {
            if (Q.find(i.first)!=Q.end())
            {
                int possibleNewDistance= distance+ i.second;
                if (possibleNewDistance<Q[i.first])
                {   
                    Q[i.first]=possibleNewDistance;
                    previous[i.first]=currentVertex;
                    if(currentVertex==start) previous[currentVertex]="";
                }
            }  
        }
    }
    std::cout<<"You cannot reach crossroad 2 from crossroad 1\n";
}


std::pair<std::list<std::string>, int> Algorithms:: DiikstraReturn (std::string start, std:: string finish)
{
    std::pair<std::list<std::string>, int> result;
    if (!loadedGraph.getGraph().existsVertex(start) || !loadedGraph.getGraph().existsVertex(finish))
    {
        std::cout<<"There is an invalid name among the written above";
        std::cout<<'\n';
        return result ;
    }
    std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map =loadedGraph.getGraph().getMyGraph();
    std::unordered_map<std::string, int> Q;
    std::map<std::string, std::string> previous;
    for(auto const& i: map)
    {
        Q.insert(std::make_pair(i.first, INF));
    }
    Q[start]=0; 
    std::string currentVertex;
    std::list<std::string> finalNodeSequence;
    while (!Q.empty())
    {
        int min=INF;
        for(auto const& i: Q)
        {
            if(i.second<=min)
            {
                min=i.second;
                currentVertex=i.first;
            }
        }
        int distance = Q[currentVertex];
        Q.erase(currentVertex);
        if(currentVertex==finish)
        {
            if(distance!=INF)
            {
                std::string elementToAdd=finish;
                while(elementToAdd!="")
                {
                    finalNodeSequence.push_front(elementToAdd);
                    elementToAdd=previous[elementToAdd];
                }
                result.first=finalNodeSequence;
                result.second=distance;
                return result;
            }
        }
        for (auto const& i: map[currentVertex])
        {
            if (Q.find(i.first)!=Q.end())
            {
                int possibleNewDistance= distance+ i.second;
                if (possibleNewDistance<Q[i.first])
                {   
                    Q[i.first]=possibleNewDistance;
                    previous[i.first]=currentVertex;
                    if(currentVertex==start) previous[currentVertex]="";
                }
            }  
        }
    }
    std::cout<<"You cannot reach crossroad 2 from crossroad 1\n";
    return result;
}
