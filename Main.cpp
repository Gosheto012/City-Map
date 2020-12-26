#include"Graph.cpp"
#include"Data.cpp"
#include"Algorithms.cpp"
int main ()
{
   
 
    Algorithms a ("Map.txt"); 
    a.loadDataFromFile("Map.txt");
    a.printGraph();
    a.getData().printGraph();
    std::cout<<a.isReachable("Mama", "Tati");
    std::cout<<'\n';
    std::cout<<a.canReturnToSamePlace("FMI");
    std::cout<<'\n';
    std::cout<<a.canReachAllOthers("Centur");
    std::cout<<'\n';
    a.printOneWayStreets();
    std::cout<<'\n';
    std::cout<<a.samePowerEachEdge();
    std::cout<<'\n';
    a.printEulerianPathIfAvailable();
    return 0;
}
