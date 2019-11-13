class Devices
{
    private:
        std::string playerName;
        int device_ID;
        int session_ID;

    public:
        Devices(std::string name, int device, int session) { playerName = name; device_ID = device; session_ID = session;}
        int getID() { return device_ID;}
        int getSession() { return session_ID;}
        std::string getPlayer() { return playerName;}
};

class Game
{
    private:
       std::string file_name;
       bool is_game;
       int session_id, datetime;
    public:
        Game(std::string n, bool g, int s, int d) { session_id = s; file_name = n; is_game = g; datetime = d;}
        std::string get_name() { return file_name; }
        int get_id() { return session_id;}
};
