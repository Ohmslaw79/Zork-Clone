#include "parsexml.h"
#include "game.h"
#include <string>

int main() //for playing
{
    std::cout << "Loading sample.xml" << std::endl
              << std::endl;
    game_ptr GI = load_xml("./data/sample.xml"); //load xml into a game instance
    int status = 1;
    string command;
    GI->start_game("Entrance");

    while (status == 1)
    {
        std::cout << std::endl
                  << "- ";
        std::getline(std::cin, command);
        status = GI->parse_command(command, false);
    }
}