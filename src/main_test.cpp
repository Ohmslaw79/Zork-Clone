#include "parsexml.h"
#include "game.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

int main() //for testing
{
    vec_str filenames;
    filenames.push_back("containersample");
    filenames.push_back("creaturesample");
    filenames.push_back("itemsample");
    filenames.push_back("roomsample");
    filenames.push_back("triggersample");
    std::ifstream fo;

    for (auto filename : filenames)
    {
        std::cout << "--Loading " << filename << ".xml--" << std::endl
                  << std::endl;
        game_ptr GI = load_xml("./data/" + filename + ".xml"); //load xml into a game instance
        int status = 1;
        string command;
        GI->start_game("Entrance");
        fo.open("./data/" + filename + ".txt");
        assert(fo.good() == true);

        while (status == 1)
        {
            std::cout << std::endl
                      << "- ";
            string command;
            std::getline(fo, command);
            if (!command.empty())
            {
                std::cout << command << std::endl;
                status = GI->parse_command(command, false);
            }
            else
            {
                status = 0;
            }
        }
        fo.close();
        std::cout << "------------------------------------" << std::endl;
    }
}