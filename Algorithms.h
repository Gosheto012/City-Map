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
    
    void loadData (std::string file);
    bool existsVertex (std::string vertexName);
    bool isReachable(std::string start, std::string finish);
    bool canReturnToSamePlace (std::string start);
    bool canReachAllOthers (std::string start);
    bool stringsBelongInArray (std::string str, std::vector<std::string> strArray);
    bool isNoWayCrossroad (std::string start);
    void printOneWayStreets ();


    void traverse (std::string name, std:: unordered_map< std::string, std:: list<std:: pair<std::string, int> > > map, std::unordered_map<std::string, bool>& m);
    bool isConnected ();
    bool samePowerEachEdge ();
    void printEulerianPathIfAvailable ();

    void Diikstra (std::string start, std:: string finish);
    std::pair<std::vector<std::string>, int> DiikstraReturn (std::string start, std:: string finish, std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map);
    std::vector<std::pair<std::vector<std::string>, int> > threeShortestPathsHelper (std::string start, std::string finish, Graph graph);
    std::pair<std::vector<std::string>, int>  addCostToListandReturnShortest (std::list<std::pair<std::vector<std::string>, int>> B, Graph graph);
    std::list<std::pair<std::string, int>> returnListVertex (std::string vertexName,  std::unordered_map< std::string, std:: list<std:: pair<std::string, int>>> map);

    void printThreeShortestPaths (std::vector<std::pair<std::vector<std::string>, int> >& A);
    void threeShortestPaths (std::string start, std::string finish);
    void threeShortestPathsAfterClosing (std::string start, std::string finish);

    Data getData () const;
};

#endif
