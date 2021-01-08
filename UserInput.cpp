#include"UserInput.h"

UserInput:: UserInput (std::string file)
{
	map.loadData(file);
}

void UserInput:: cityMenu () const
{
    	std::cout << "************************************** WELCOME TO THE CITY! **************************************" << std::endl;
	std::cout << "* 0. Take a look at the city map                                                                 *" << std::endl;
	std::cout << "* 1. Check if exists a path between two crossroads                                               *" << std::endl;
    	std::cout << "* 2. Find three shortest paths between two crossroads                                            *" << std::endl;
	std::cout << "* 3. Find three shortest paths between two crossroads after you give a list of closed crossroads *" << std::endl;
	std::cout << "* 4. Check if we can return to the same crossroad where we have started from                     *" << std::endl;
   	 std::cout << "* 5. Check if we can make a city tour and print the path if we can                               *" << std::endl;
    	std::cout << "* 6. Check if we can reach all other crossroads from a single one                                *" << std::endl;
	std::cout << "* 7. Print all one way streets                                                                   *" << std::endl;
	std::cout << "* 8. Show these instrucions again                                                                *" << std::endl;
	std::cout<<  "* 9. Enter the interactive mode                                                                  *" << std::endl;
	std::cout<<  "* 10. Exit the program                                                                           *" << std::endl;
	std::cout << "**************************************************************************************************" << std::endl;
}


void UserInput:: interactiveMenu () const
{
    	std::cout << "********************************************** INTERACTIVE MODE **********************************************" << std::endl;
	std::cout << "* 0. Take a look at the city map                                                                             *" << std::endl;
	std::cout << "* 1. LOCATION: Show your location                                                                            *" << std::endl;
    	std::cout << "* 2. CHANGE @CROSSROAD: Change your location to a crossroad you write                                        *" << std::endl;
	std::cout << "* 3. NEIGHBOURS: Show all the neighboring crossroad from your location                                       *" << std::endl;
	std::cout << "* 4. MOVE @CROSSROAD: Change your location to a crossroad you write if possible and print the route to there *" << std::endl;
    	std::cout << "* 5. CLOSE @CROSSROAD: Close a crossroad                                                                     *" << std::endl;
    	std::cout << "* 6. OPEN @CROSSROAD: Open a crossroad                                                                       *" << std::endl;
	std::cout << "* 7. CLOSED: Show all closed crossroads                                                                      *" << std::endl;
	std::cout << "* 8. TOUR: Print the path of the city tour from your location                                                *" << std::endl;
	std::cout<<  "* 9. Show these instructions again                                                                           *" << std::endl;
	std::cout<<  "* 10. Exit the interactive mode                                                                              *" << std::endl;
	std::cout << "**************************************************************************************************************" << std::endl;
}


void UserInput:: printCity () const
{
	std::cout<<"The city looks like this:\n";
	map.getData().getGraph().print();
}


void UserInput:: userInputSingleCrossroad (std::string& vertexName)
{
	do
    {
        std::cout<<"Please write the name of the crossroad: ";
	    std::cin>>vertexName;
		if(!map.existsVertex(vertexName))
		{
			std::cout<<"Please write the name of an existing crossroad!\n";
		}
    } while (!map.existsVertex(vertexName));
	return;
}


void UserInput:: userInputTwoCrossroads (std::string& start, std::string& finish)
{
	do
    {
        std::cout<<"Please write the name of the first crossroad: ";
	    std::cin>>start;
	    std::cout << "Please write the name of the second crossroad: ";
	    std::cin>>finish;
		if(!map.existsVertex(start) || !map.existsVertex(finish))
		{
			std::cout<<"Please write names of two existing crossroads!\n";
		}
    } while (!map.existsVertex(start) || !map.existsVertex(finish));
	return;
}


void UserInput:: isReachable ()
{
    std::string start;
    std::string finish;
    userInputTwoCrossroads(start, finish);
	std:: unordered_map< std::string, std:: list<std:: pair<std::string, int>>> graph= map.getData().getGraph().getMyGraph();
	if(map.isReachable(start, finish, graph))
	{
		std::cout<<"Yes, you can reach crossroad "<<finish<<" from crossroad "<<start<<'\n';
		return;
	}
	else
	{
		std::cout<<"No, you cannot reach crossroad "<<finish<<" from crossroad "<<start<<'\n';
		return;
	}
}


void UserInput:: threeShortestPaths ()
{
	std::string start;
    std::string finish;
    userInputTwoCrossroads(start, finish);
	map.threeShortestPaths(start, finish);
	return;
}


void UserInput:: threeAlternativeShortestPaths ()
{
	std::string start;
    std::string finish;
	userInputTwoCrossroads(start, finish);
	map.threeShortestPathsAfterClosing(start, finish);
	return;
}


void UserInput:: canReturnToSamePlace ()
{
	std::string vertexName;
	userInputSingleCrossroad(vertexName);
	if(map.canReturnToSamePlace(vertexName))
	{
		std::cout<<"Yes, you can return to the same crossroad!\n";
	}
	else
	{
		std::cout<<"No, you cannot return to the same crossroad!\n";
	}
	return;
}



void UserInput:: cityTour ()
{
	map.printEulerianPathIfAvailable(map.getData().getGraph().getMyGraph(), false, "");
	return;
}


void UserInput:: canReachAllOthers ()
{
	std::string vertexName;
	userInputSingleCrossroad(vertexName);
	if(map.canReachAllOthers(vertexName))
	{
		std::cout<<"Yes, you can reach all other crossroads from crossroad "<<vertexName<<" !\n";
	}
	else
	{
		std::cout<<"No, you cannot reach all other crossroads from crossroad "<<vertexName<<" !\n";
	}
	return;
}


bool UserInput:: isClosed (std::string vertexName)
{
	for(std::list<std::string>::iterator it=closedCrossroads.begin(); it!=closedCrossroads.end(); it++)
	{
		if(vertexName==*it) return true;
	}
	return false;
}


void UserInput:: closeGraph(Graph& graph) 
{
	for(auto const& i:graph.getMyGraph())
	{
		if(isClosed(i.first))
		{
			graph.removeVertex(i.first);
		}
	}
	return;
}


void UserInput:: oneWayStreets ()
{
	map.printOneWayStreets();
	return;
}

void UserInput:: startLocation ()
{
	std::string start;
	do {
		std::cout<<"Please write the name of the location you want to start from: ";
		std::cin>>start;
		if(!map.existsVertex(start))
		{
			std::cout<<"Please write the name of a existing crossroad!\n";
		}
	} while (!map.existsVertex(start));
	location=start;
	return;
}


void UserInput:: changeLocation ()
{
	std::string vertexName;
	userInputSingleCrossroad(vertexName);
	if(isClosed(vertexName))
	{
		std::cout<<"The chosen crossroad is closed! You cannot change your location to there!\n";
		return;
	}
	location=vertexName;
	return;
}


void UserInput:: printNeighbours ()
{
	std::unordered_map<std::string, std:: list<std::pair<std::string, int>>> currentGraph=map.getData().getGraph().getMyGraph();
	std::cout<<"The neighbours of the crossroad called "<<location<<" are:\n";
	for(auto const& i: currentGraph)
	{
		if(i.first==location)
		{
			if(currentGraph[i.first].empty())
			{
				std::cout<<"There are not any neighbours of the crossroad called"<<location<<"!\n";
				return;
			}
			for(std::list<std::pair<std::string, int>>::iterator j=currentGraph[i.first].begin(); j!=currentGraph[i.first].end(); j++)
			{
				std::pair<std::string, int> p=*j;
				std::cout<<p.first<<", ";
			}
		}
	}
	std::cout<<'\n';
	return;
}


void UserInput:: move()
{
	std::string vertexName;
	userInputSingleCrossroad(vertexName);
	if(isClosed(vertexName))
	{
		std::cout<<"You cannot go to the crossroad called "<<vertexName<<" because it is closed!\n";
		return;
	}
	Graph graph = map.getData().getGraph();
	closeGraph(graph);
	if(!map.isReachable(location, vertexName, graph.getMyGraph()))
	{
		std::cout<<"You cannot reach the crossroad called "<<vertexName<<" from your location because either";
		std::cout<<" there is no connection between at all or the closed crossroads block their connection!\n";
		return;
	}
	std::vector<std::string> path = map.DiikstraReturn(location, vertexName, graph.getMyGraph()).first;
	std::cout<<"The route to the crossroad called "<<vertexName<<" is:\n";
	for(int i=0; i<path.size(); i++)
	{
		if(i!=path.size()-1) std::cout<<path[i]<<" -> ";
	}
	std::cout<<'\n';
	location=vertexName;
	return;
}


void UserInput:: addClosedCrossroad ()
{
	std::string vertexName;
	userInputSingleCrossroad(vertexName);
	if(isClosed(vertexName))
	{
		std::cout<<"This crossroad is already closed!\n";
		return;
	}
	closedCrossroads.push_back(vertexName);
	return;
}


void UserInput:: openCrossroad()
{
	std::string vertexName;
	userInputSingleCrossroad(vertexName);
	if(!isClosed(vertexName))
	{
		std::cout<<"This crossroad is already open!\n";
		return;
	}
	for(std::list<std::string>::iterator i=closedCrossroads.begin(); i!=closedCrossroads.end(); i++)
	{
		if(*i==vertexName)
		{
			closedCrossroads.erase(i);
			break;
		}
	}
	return;
}


void UserInput:: printClosedCrossroads ()
{
	if(closedCrossroads.empty())
	{
		std::cout<<"There are not any closed crossroads!\n";
		return;
	}
	std::cout<<"The closed crossroads are:\n";
	for(std::list<std::string>::iterator i=closedCrossroads.begin(); i!=closedCrossroads.end(); i++)
	{
		std::cout<<*i;
		if(*i!=closedCrossroads.back()) std::cout<<", ";
	}
	std::cout<<'\n';
	return;
}


void UserInput:: interactiveTour ()
{
	Graph graph = map.getData().getGraph();
	closeGraph(graph);
	map.printEulerianPathIfAvailable(graph.getMyGraph(), true, location);
	return;
}


void UserInput:: interactive ()
{
	startLocation();
	interactiveMenu();
	int command;
	do {
		std::cout<<"Please enter your command: ";
		std::cin>>command;
		if(command==10)
		{
			std::cout<<"Exiting the interactive mode...\n";
		}
		switch (command) {
		case 0: {
			printCity();
			break;
		}
		case 1: {
			std::cout<<"Your current location is: "<<location<<'\n';
			break;
		}
		case 2:{
			changeLocation();
			break;
		}
		case 3:{
			printNeighbours();
			break;
		}
		case 4:{
			move();
			break;
		}
		case 5:{
			addClosedCrossroad();
			break;
		}
		case 6:{
			openCrossroad();
			break;
		}
		case 7:{
			printClosedCrossroads();
			break;
		}
		case 8:{
			interactiveTour();
			break;
		}
		case 9:{
			interactiveMenu();
			break;
		}
		case 10:{
			break;
		}
		default: std::cout<<"Please enter a valid command from the interactive menu!\n";
		}
	} while (command!=10);
	return;
}


void UserInput:: run ()
{
	cityMenu ();
	int command;
	do {
		std::cout<<"Please enter your command: ";
		std::cin>>command;
		if(command==10)
		{
			std::cout<<"Exiting the program...\n";
		}

		switch (command) {
		case 0: {
			printCity();
			break;
		}
		case 1: {
			isReachable();
			break;
		}
		case 2: {
			threeShortestPaths();
			break;
		}
		case 3: {
		    threeAlternativeShortestPaths();
			break;
		}
		case 4:{
			canReturnToSamePlace();
			break;
		}
		case 5: {
			cityTour();
			break;
		}
		case 6: {
			canReachAllOthers();
			break;
		}
		case 7: {
			oneWayStreets();
			break;
		}
		case 8: {
			cityMenu();
			break;
		}
		case 9: {
			interactive ();
			cityMenu();
			break;
		}
		case 10:{
			break;
		}
		default: std::cout<<"Please enter a valid command from the city menu!\n";
		}
	} while (command!=10);
	return;
}
