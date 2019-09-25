#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

int main()
{
    std::ifstream file ("ncst2018");
    std::string input, athleteName; 
    
    // We don't need every 10th of a second, so I will use this to only take every second of data 
    int lineNumbers = 0; 
    
    while (file >> input)
    {
        // This portion will continue to scan until it finds "Athlete". Once it has found "athlete"
        // it will start a separate while loop where it will continue to write to the individual 
        // player's file. You WILL need to create a players directory. I am unsure if it will automatically
        // create it for you
        
        if(input == "#" && file >> input && input == "Athlete:")
        {
            file >> input; 
            // grab athlete name && reset lineNumbers to 0 for each athlete
            athleteName = input; lineNumbers = 0;
            std::cout << "Athlete name: " << athleteName << " \nLine Number: " << lineNumbers << std::endl;
            std::ofstream output;
            std::string location = "players/";
            location += athleteName;
            output.open(location); 
            //while(file >> input && input != "#")
            while(std::getline(file, input) && input.at(0) != '#') 
            {  
                // We are collecting data every 10th of a second, so I'm trimming away a bunch of data we don't need 
                if((lineNumbers % 10 == 0) & (lineNumbers != 0)) 
                {
                    std::cout << "LineNumber: " << lineNumbers << std::endl;
                    output << input;// << std::endl;
                    lineNumbers++;
                }

                lineNumbers++;
            }
            output.close();
        }
         
    }

    file.close(); 
    return 0;
}
