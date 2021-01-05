#include"UserInput.h"

int main ()
{
  std::string fileName;
  std::cout<<"Please enter the name of the file in order to load the map: ";
  std::cin>>fileName;
  UserInput runner(fileName);
  runner.run();
  return 0;
} 
