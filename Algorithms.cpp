#include"Algorithms.h"
#define INF  std::numeric_limits<int>::max()


void Algorithms:: loadData (std::string file)
{
    loadedGraph.loadDataFromFile(file.c_str());
}


bool Algorithms:: existsVertex (std::string vertexName)
{
    return loadedGraph.getGraph().existsVertex(vertexName);
}


bool Algorithms:: stringsBelongInArray (std::string str, std::vector<std::string> strArray)
{
    for(size_t i=0; i<strArray.size(); ++i)
    {
        if(strArray[i]==str) return true;
    }
    return false;
}

bool Algorithms:: isReachable (std::string start, std::string finish, std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map)
{
    if (start==finish) return true;
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
    std::cout<<"All one-way streets are:\n";
    bool flag=false;
    for(auto const& i: map)
    {
        std::string Node = i.first;
        std::list<std::pair < std::string, int> > otherNodes = i.second; 
        for(auto const& j: otherNodes)
        {
            if(isNoWayCrossroad(j.first))
            {
                std::cout<<Node<<" - "<<j.first<<'\n';
                flag=true;
            }
        }
    }
    if(!flag) std::cout<<"There are not any one-way streets!\n";
}



bool Algorithms:: samePowerEachEdge (std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map)
{
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


bool Algorithms:: isConnected (std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map)
{
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


void Algorithms:: printEulerianPathIfAvailable (std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map, bool flag, std::string location)
{
    if(!samePowerEachEdge(map) || !isConnected(map))
    {
        std::cout<<"You cannot cross all the streets without repeating\n";
        return;
    }
    std::cout<<"An example of a city tour is the following route:\n";
    std::unordered_map<std::string,int> edge_count; 
  
    for (auto const& i: map) 
    { 
        edge_count.insert (std::make_pair(i.first, i.second.size()));
    } 
  
    std::stack<std::string> curr_path; 
  
    std::vector<std::string> circuit; 
    std::string curr_v;

    if (!flag)
    {
        curr_path.push(map.begin()->first); 
        curr_v = map.begin()->first; 
    }
    else
    {
        curr_path.push(location); 
        curr_v = location; 
    }
    
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
    if(circuit.empty()) std::cout<<"You cannot make a city tour";
    std::cout<<'\n'; 

}


std::pair<std::vector<std::string>, int> Algorithms:: DiikstraReturn (std::string start, std:: string finish, std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map)
{
    std::pair<std::vector<std::string>, int> result;
    if(!isReachable(start, finish, map)) return result;
    std::unordered_map<std::string, int> Q;
    std::map<std::string, std::string> previous;
    for(auto const& i: map)
    {
        Q.insert(std::make_pair(i.first, INF));
    }
    Q[start]=0; 
    std::string currentVertex;
    std::vector<std::string> finalNodeSequence;
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
                    finalNodeSequence.insert(finalNodeSequence.begin(),elementToAdd);
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
    return result;
}


std::pair<std::vector<std::string>, int> Algorithms:: addCostToListandReturnShortest (std::list<std::pair<std::vector<std::string>, int>> B, Graph graph)
{
    int crrMin=INF;
    std::pair<std::vector<std::string>, int> result;
    for(std::list<std::pair<std::vector<std::string>, int>>::iterator it=B.begin(); it!=B.end(); it++)
    {
        std::pair<std::vector<std::string>, int> myPair=*it;
        for(int i=0; i<myPair.first.size()-1; i++)
        {
            myPair.second+=graph.getDistanceConnectedNodes(myPair.first[i], myPair.first[i+1]);
        }

        if(crrMin>myPair.second)
        {
            result=myPair;
            crrMin=myPair.second;
        } 
    }
    return result;
}


std::list<std::pair<std::string, int>> Algorithms:: returnListVertex (std::string vertexName, std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map)
{
    return map[vertexName];
}


std::vector<std::pair<std::vector<std::string>, int> > Algorithms:: threeShortestPathsHelper (std::string start, std::string finish, Graph graph)
{
    std::vector<std::pair<std::vector<std::string>, int> > A;
    std::list<std::pair<std::vector<std::string>, int>> B;
    if (!isReachable(start, finish, graph.getMyGraph())) return A;
    A.push_back(DiikstraReturn(start, finish, graph.getMyGraph()));
    bool flag=false;
    for(int k=1; k<=2; k++)
    {
        flag=false;
        for(int i=0; i<=A[k-1].first.size()-2; i++)
        {
            flag=false;
            std::string spurNode=A[k-1].first[i];
            std::vector<std::string> rootPath;
            std::unordered_map<std::string, std::list<std::pair<std::string, int>>> vertexSave;
            std::list<std::pair<std::string, std::pair<std::string, int>>> newEdgesSave;
            for(int s=0; s<=i; s++) rootPath.push_back(A[k-1].first[s]);
            for(int p=0; p<A.size(); p++)
            {
                std::vector<std::string> pNodes;
                int min=A[p].first.size()-1;
                if(min>i) min=i;
                for(int s=0; s<=min; s++)
                {
                    pNodes.push_back(A[p].first[s]);
                }
                if(pNodes==rootPath)
                {
                    std::string vertex1= A[p].first[i];
                    std::string vertex2=A[p].first[i+1];
                    int distance=graph.getDistanceConnectedNodes(vertex1, vertex2);
                    std::pair<std::string, int> pair2=std::make_pair(vertex2, distance);
                    std::pair<std::string, std::pair<std::string, int>> mainPair= std::make_pair(vertex1, pair2);
                    newEdgesSave.push_back(mainPair);
                    if(graph.existsVertex(vertex1) && graph.existsVertex(vertex2))graph.removeEdge(vertex1, vertex2);
                }
            }

            for (int s=0; s<rootPath.size(); s++)
            {
                //std::cout<<rootPath[s]<<", ";
                if(rootPath[s]!=spurNode)
                {
                    vertexSave.insert(std::make_pair(rootPath[s], returnListVertex(rootPath[s], graph.getMyGraph())));
                    if(graph.existsVertex(rootPath[s]))graph.removeVertex(rootPath[s]);
                } 
            }

            if(DiikstraReturn(spurNode, finish, graph.getMyGraph()).second>0 && DiikstraReturn(spurNode, finish, graph.getMyGraph()).second<INF)
            {
                std::vector<std::string> spurPath =DiikstraReturn(spurNode, finish, graph.getMyGraph()).first;
                bool destinationFlag=false;
                std::vector<std::string> totalPath;
                for(int s=0; s<rootPath.size(); s++)
                {
                    totalPath.push_back(rootPath[s]);
                }
                for(int s=1; s<spurPath.size(); s++)
                {
                    totalPath.push_back(spurPath[s]);
                }
                if(totalPath[totalPath.size()-1]!=finish) destinationFlag=true;
                for(std::list<std::pair<std::vector<std::string>, int>>::iterator it=B.begin(); it!=B.end(); it++)
                {
                    std::pair<std::vector<std::string>, int> myPair=*it;
                    if(totalPath==myPair.first)
                    {
                        flag=true;
                        break;
                    } 
                }
                if(!flag && !destinationFlag)
                {
                    B.push_back(std::make_pair(totalPath, 0));
                }

            }
            
            for(auto const& q: newEdgesSave)
            {
                graph.addEdge(q.first, q.second.first, q.second.second);
            }


            for(auto const& q: vertexSave)
            {
                graph.addVertex(q.first, q.second);
            }

            vertexSave.clear();
            newEdgesSave.clear();
        }
        if(B.empty()) break;
        A.push_back(addCostToListandReturnShortest(B, graph));
        for(std::list<std::pair<std::vector<std::string>, int>>::iterator it=B.begin(); it!=B.end(); it++)
        {
            std::pair<std::vector<std::string>, int> myPair=*it;
            if(myPair.first==A[k].first)
            {
                B.erase(it);
                break;
            }
        }
    }
    return A;
}


void Algorithms:: printThreeShortestPaths (std::vector<std::pair<std::vector<std::string>, int> >& A)
{
    if(A.size()==0)
    {
        std::cout<<"There is no path betweeen these crossroads!\n";
        return;
    }
    else if(A.size()==1)
    {
        std::cout<<"There is only one path between these crossroads and it is:\n";
        for(int i=0; i<A[0].first.size(); i++)
        {
            std::cout<<A[0].first[i]<<" -> ";
        }
        std::cout<<A[0].second<<'\n';
        return;
    }
    else if (A.size()==2)
    {
        std::cout<<"There are only two paths between these crossroads and they are:\n";
        for(int i=0; i<A.size(); i++)
        {
            for(int j=0; j<A[i].first.size(); j++)
            {
                std::cout<<A[i].first[j]<<" -> ";
            }
            std::cout<<A[i].second<<'\n';
        }
        return;
    }
    else
    {
        std::cout<<"The three shortest paths between these crossroads are:\n";
        for(int i=0; i<A.size(); i++)
        {
            for(int j=0; j<A[i].first.size(); j++)
            {
                std::cout<<A[i].first[j]<<" -> ";
            }
            std::cout<<A[i].second<<'\n';
        }
        return;
    }
}


void Algorithms:: threeShortestPaths (std::string start, std::string finish)
{
    std::vector<std::pair<std::vector<std::string>, int> > A= threeShortestPathsHelper(start, finish, loadedGraph.getGraph());
    printThreeShortestPaths(A);
    return;
}


void Algorithms:: threeShortestPathsAfterClosing (std::string start, std::string finish)
{
    Graph graph = loadedGraph.getGraph();
    int n;
    std::vector<std::string> closedCrossroads;
    std::cout<<"Enter the number of crossroads you want to close: ";
    do
    {
        std::cin>>n;
        if(n<=0 || n>graph.getMyGraph().size()) 
        std::cout<<"Please enter a number bigger than zero and no bigger than the number of crossroads!\n";
    } while (n<=0 || n>graph.getMyGraph().size());
    std::cout<<"Now enter the names of the crossroads you want to close one by one:\n";
    for(int i=0; i<n; i++)
    {
        std::string currentCrossroad;
        std::cin>>currentCrossroad;
        if(graph.existsVertex(currentCrossroad) && currentCrossroad!=start && currentCrossroad!=finish) closedCrossroads.push_back(currentCrossroad);
        else if (graph.existsVertex(currentCrossroad) && (currentCrossroad==start || currentCrossroad==finish))
        {
            std::cout<<"Please remove a crossroad different from the start or finish! Otherwise, the task is pointless!\n";
            i--;
        }
        else 
        {
            std::cout<<"There is no vertex called "<<currentCrossroad<<" in the graph!\n";
            std::cout<<"Please enter a valid name of a vertex!\n";
            i--;
        }
    }
    for(int i=0; i<closedCrossroads.size(); i++)
    {
        graph.removeVertex(closedCrossroads[i]);
    }
    std::vector<std::pair<std::vector<std::string>, int> > A=threeShortestPathsHelper(start, finish, graph);
    printThreeShortestPaths(A);
    return;
}


Data Algorithms:: getData () const
{
    return loadedGraph;
}
