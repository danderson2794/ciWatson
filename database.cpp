#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <unordered_map>
#include "database.h"

void getGameSessions(std::ifstream&);
void getDeviceID();
void createTable();
void createPlayerTable();

std::vector<Game> games;
std::vector<Devices> devices;
std::unordered_map<std::string, bool> playerMap;
std::pair<std::string, int> playerTable;
std::vector<std::pair<std::string, int> > playerTableMain;


int main()
{
    std::ifstream sessions("sessions");

    getGameSessions(sessions);
    std::cout << "Game size is: " << games.size() << std::endl;
    getDeviceID(); 
    sessions.close();

    std::ofstream file("devices");   
    std::cout << "Device size " << devices.size() << std::endl; 
    // Creating the table for Devices
    for(int i = 0; i < static_cast<int>(devices.size()); i++)
    {
        file << devices[i].getID() << "," << devices[i].getPlayer() << "," << devices[i].getSession() << "\n";
    }
    file.close();

    std::cout << "Creating player table...\n";
    createPlayerTable();

    std::cout << "Now populating the table.." << std::endl;
    createTable();

    std::ofstream f("players.txt");

    std::cout << "Size of map is: " << playerMap.size() << std::endl;
    int playerCount = 0;
    for(auto x : playerMap)
    {
        playerTableMain.push_back(std::make_pair(x.first, playerCount));
        playerCount++;   
    }
    
    for(auto x : playerTableMain)
    {
        f << x.first << "," << x.second << std::endl;
    }

    


    return 0;
}

void createPlayerTable()
{
    std::ofstream file("players");
    std::unordered_map<std::string, std::vector<int> > playerData;


}



void createTable()
{
    
    for(int i = 0; i < static_cast<int> ( games.size() ); i++)
    {
        std::string gameName = "games/";
        // You will need a directory of 'games' that have all the files inside it
        gameName += games[i].get_name(); 
        // This will be used to iterate over the table.
        std::ifstream gameFile(gameName);
        gameFile.clear();
        gameFile.seekg(0, std::ios::beg);
        // This will be used to write to the table
        std::ofstream table("table");
        std::string temp = "";
        int player = 0;
        std::cout << "Inside " << gameName << std::endl;
        while(std::getline(gameFile, temp) )
        {
            // Iterate through the header data 
            while(std::getline(gameFile, temp) && temp[0] == '#') {
            }      
            // This will grab the "timestamp, Seconds, Velocity, ..." line
            // Now we're going to grab game data and output it to our table file
            while(std::getline(gameFile, temp) && temp[0] != '#')
            {
                table << devices.at(player).getID() << "," << devices.at(player).getPlayer() << "," << devices.at(player).getSession() << ",";
                table << temp; 
            } 
            player++; 
        }
    }
}


void getDeviceID()
{
    // I will iterate through each game and start grabbing data. 
    for(int i = 0; i < static_cast<int>( games.size() ) ; i++)
    {
        std::string filename = "games/"; 
        filename += games[i].get_name(); 
        std::cout << "inside " << filename << "\n"; 
        std::ifstream file(filename);
        std::string temp; 
        int id = 0;
        std::string athlete;
        // This will iterate and grab the ID number, then grab the player 
        while(file >> temp)
        {
            bool placeBack = false;
            athlete.erase();
            if(temp == "DeviceId")
            {
                file >> temp >> id;
                placeBack = true;
                // If we're here, we know the athlete's name will be below the device id, so 
                // We want to grab his name. That's what this do-while loop does. 
                do
                {
                    file >> temp;
                } while ( temp != "Athlete:");
            }
            if(temp == "Athlete:")
            {
                file >> athlete;
                // This cleans up the source file, so we only get the player's name without "" 
                for(int te = 0; te < static_cast<int> (athlete.size()); te++)
                {
                    if(athlete[te] == '"') athlete.erase(athlete.begin() + te);
                }
            }
            if (placeBack)
            {
                Devices tempD(athlete, id, games[i].get_id());
                devices.push_back(tempD);
                playerMap[athlete] = true;
            }
        }
        file.close(); 
    }
}


void getGameSessions(std::ifstream& sessions)
{
    // These temp variables will be used to populate the games vector
    std::string name;
    bool is_game;
    int session_id, date;
    while(sessions >> name >> session_id >> is_game >> date)
    {
        Game temp(name, is_game, session_id, date);
        games.push_back(temp);
    }
}