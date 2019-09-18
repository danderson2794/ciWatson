#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

int main()
{
    std::ifstream file ("ncst2018");
    std::string input, athleteName; 
    while (file >> input)
    {
        // This portion will continue to scan until it finds "Athlete". Once it has found "athlete"
        // it will start a separate while loop where it will continue to write to the individual 
        // player's file. You WILL need to create a players directory. I am unsure if it will automatically
        // create it for you
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
                output << input << " " << std::endl;
            }
        }
         
    } 
    return 0;
}
