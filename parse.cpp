#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    std::ifstream file ("ncst2018");
    std::string input, athleteName; 
    while (file >> input)
    {
//        std::cout << "here\n";
        if(input == "#" && file >> input && input == "Athlete:")
        {
            file >> input; // grab athlete name
            athleteName = input; 
            std::cout << "Athlete name: " << athleteName << std::endl;
            std::ofstream output;
            std::string location = "players/";
            location += athleteName;
            output.open(location); 
            while(file >> input && input != "#")
            {   
                output << input << " " << endl;

            }
        }
         
    } 
    return 0;
}
