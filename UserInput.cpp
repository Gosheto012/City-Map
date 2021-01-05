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
	std::cout<<  "* 9. Exit the program                                                                            *" << std::endl;
	std::cout << "**************************************************************************************************" << std::endl;
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
			std::cout<<"Please write names of an existing crossroad!\n";
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
	if(map.isReachable(start, finish))
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



void UserInput:: cityTour () //5
{
	map.printEulerianPathIfAvailable();
}


void UserInput:: canReachAllOthers () //6
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


void UserInput:: oneWayStreets ()
{
	map.printOneWayStreets();
	return;
}


void UserInput:: run ()
{
	cityMenu ();
	int command;
	do {
		std::cout<<"Please enter your command: ";
		std::cin>>command;
		if(command==9)
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
			break;
		}
		default: std::cout<<"Please enter a valid command from the city menu!\n";
		}
	} while (command!=9);
	return;
}
