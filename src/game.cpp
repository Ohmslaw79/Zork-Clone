#include "game.h"

//TODO -- Finish up output text for everything

Game::Game() : player(new Player())
{
    printv("----Creating New Game Instance----");
    containers[inventory] = player;
}

//Private:

void Game::take_item(string item) //Needs to be updated to be able to work with containers
{
    string taken_item;
    bool item_taken = false;
    for (auto container : player->can_access())
    {
        if (container != inventory)
        {
            taken_item = containers[container]->take_item(item);
            if (taken_item != "")
            {
                player->add_to_inventory(taken_item);
                output(taken_item + " added to inventory\n");
                item_taken = true;
            }
        }
    }
    if (!item_taken)
    {
        output("Cannot take " + item + "\n");
    }
}

void Game::drop_item(string item)
{
    string dropped_item = player->take_item(item);
    if (dropped_item != "")
    {
        rooms[player->get_current_room()]->add_item(dropped_item);
        output("You drop the " + item + " on the ground" + "\n");
    }
    else
    {
        output("You are not carrying a " + item + "\n");
    }
}

void Game::put_item(string item, string container)
{
    if (containers.find(container) != containers.end())
    {
        if (player->can_access(container) || containers.at(container)->accepts(item))
        {
            string removed_item = player->take_item(item);
            if (removed_item != "")
            {
                bool item_added = containers[container]->add_item(removed_item);
                if (item_added)
                {
                    output("You put the " + item + " in the " + container + "\n");
                }
                else
                {
                    player->add_item(removed_item);
                    output("You can't put that in the " + container + "\n");
                }
            }
            else
            {
                output("You are not carrying a " + item + "\n");
            }
        }
        else
        {
            output("You cannot access the " + container + ". Try opening it first\n");
        }
    }
    else
    {
        output("There is not a " + container + " in the room\n");
    }
}

void Game::update_status(string object, string new_status)
{
    if (master_list.find(object) != master_list.end())
    {
        master_list[object]->set_status(new_status);
    }
}

void Game::read_item(string item)
{
    if (player->has(item))
    {
        output("You look at the " + item + "... ");
        output(items[item]->get_writing() + "\n");
    }
    else
    {
        output("You don't have a " + item + " to read\n");
    }
}

void Game::move(string direction)
{
    string new_room = rooms[player->get_current_room()]->get_border(direction);
    if (new_room != "")
    {
        player->set_current_room(new_room);
        output(rooms[new_room]->get_description() + "\n");
        printv("Current room changed to " + new_room + "\n");
    }
    else
    {
        output("You can't go " + direction + "\n");
    }
}

void Game::open(string container)
{
    if (containers.find(container) != containers.end() && rooms.at(player->get_current_room())->has(container) && containers.at(container)->can_be_opened())
    {
        player->add_opened_container(container);
        output(containers.at(container)->get_inventory());
    }
    else
    {
        output("Cannot open " + container + "\n");
    }
}

int Game::exit()
{
    if (rooms[player->get_current_room()]->get_type() == "exit")
    {
        output("Game Over!\n");
        return 0;
    }
    output("This room is not an exit\n");
    return 1;
}

int Game::check_triggers(string input, std::map<string, container_ptr> containers, std::map<string, game_obj_ptr> items)
{
    room_ptr current_room = rooms.at(player->get_current_room());
    int status = parse_command(current_room->run_triggers(input, containers, master_list));
    for (auto item : player->get_items())
    {
        status = parse_command(master_list.at(item)->run_triggers(input, containers, master_list));
    }

    for (auto object : master_list)
    {
        if (current_room->has(object.first))
        {
            status = parse_command(object.second->run_triggers(input, containers, master_list));
        }
    }
    return status;
}

void Game::attack_creature(string creature, string weapon)
{
    if (player->has(weapon))
    {
        if (creatures.find(creature) != creatures.end() && rooms.at(player->get_current_room())->has(creature))
        {
            creature_ptr creature_obj = creatures.at(creature);
            output("You assault the " + creature + " with the " + weapon + "...\n");
            if (creature_obj->is_vulnerable(weapon))
            {
                parse_command(creature_obj->attack(containers, master_list));
            }
        }
        else
        {
            output("There is not a " + creature + " in the room to attack\n");
        }
    }
    else
    {
        output("You dont have a " + weapon + " to attack with\n");
    }
}

void Game::output(string text)
{
    std::cout << text;
}

//Public:

//---Initialization
void Game::add_room(const room_ptr room)
{
    rooms[room->get_name()] = room;
    containers[room->get_name()] = room;
    master_list[room->get_name()] = room;
    printv("----Adding " + room->get_name() + " to game instance----");
}

void Game::add_container(const container_ptr container)
{
    containers[container->get_name()] = container;
    master_list[container->get_name()] = container;
    printv("----Adding " + container->get_name() + " to game instance----");
}

void Game::add_creature(const creature_ptr creature)
{
    creatures[creature->get_name()] = creature;
    master_list[creature->get_name()] = creature;
    printv("----Adding " + creature->get_name() + " to game instance----");
}

void Game::add_item(const item_ptr item)
{
    items[item->get_name()] = item;
    master_list[item->get_name()] = item;
    printv("----Adding " + item->get_name() + " to game instance----");
}

void Game::set_room(string new_room)
{
    player->set_current_room(new_room);
}

//--- Game
void Game::start_game(string starting_room)
{
    set_room(starting_room);
    output(rooms[starting_room]->get_description() + "\n");
}

int Game::parse_command(string command, bool internal)
{
    vec_str words;
    //check for open exit command
    if (command == "open exit")
    {
        return exit();
    }
    //split command
    string command_copy = command;
    while (command_copy.begin() != command_copy.end())
    {
        size_t end_of_word = command_copy.find(" ");
        string word;

        if (end_of_word < command_copy.size())
        {
            word = command_copy.substr(0, end_of_word);
            command_copy.erase(0, end_of_word + (end_of_word == command_copy.size() ? 0 : 1));
        }
        else
        {
            word = command_copy;
            command_copy.erase(0, command_copy.size());
        }
        words.push_back(word);
    }
    //parse commands
    int status = check_triggers(command, containers, master_list);
    if (!words.empty() && (!triggers_run || internal))
    {
        if (words[0] == "n")
        {
            move("north");
        }
        else if (words[0] == "s")
        {
            move("south");
        }
        else if (words[0] == "e")
        {
            move("east");
        }
        else if (words[0] == "w")
        {
            move("west");
        }
        else if (words[0] == "open")
        {
            open(words[1]);
        }
        else if (words[0] == "i")
        {
            output(player->get_inventory());
        }
        else if (words[0] == "take" && words.size() > 1)
        {
            take_item(words[1]);
        }
        else if (words[0] == "drop" && words.size() > 1)
        {
            drop_item(words[1]); //Will break if an item name is more than one word
        }
        else if (words[0] == "put" && words.size() > 3)
        {
            put_item(words[1], words[3]);
        }
        else if (words[0] == "read" && words.size() > 1)
        {
            read_item(words[1]);
        }
        else if (words[0] == "attack" && words.size() > 3)
        {
            attack_creature(words[1], words[3]);
        }
        else if (words[0] == "turn" && words[1] == "on" && words.size() > 2)
        {
            if (player->has(words[2]))
            {
                status = parse_command(items[words[2]]->turn_on());
            }
            else
            {
                output("You can't turn on the " + words[2] + "\n");
            }
        }
        else if (words[0] == "Add" && words.size() > 1 && internal)
        {
            containers.at(words[3])->add_item(words[1]);
            master_list.at(words[1])->run_triggers(command, containers, master_list);
        }
        else if (words[0] == "Delete" && words.size() > 1 && internal)
        {
            for (auto const &entry : containers)
            {
                if (entry.second->has(words[1]))
                {
                    entry.second->remove(words[1]);
                    master_list.at(words[1])->run_triggers(command, containers, master_list);
                }
            }
            for (auto const &entry : rooms)
            {
                if (entry.second->has(words[1]))
                {
                    entry.second->remove(words[1]);
                    master_list.at(words[1])->run_triggers(command, containers, master_list);
                }
            }
        }
        else if (words[0] == "Update" && words.size() > 3 && internal)
        {
            std::ostringstream status;
            std::copy(words.begin() + 3, words.end(), std::ostream_iterator<string>(status, " "));
            string temp = status.str();
            temp.pop_back();
            update_status(words[1], temp);
            master_list.at(words[1])->run_triggers(command, containers, master_list);
        }
        else if (words[0] == "print" && words.size() > 2 && internal)
        {
            std::ostringstream print;
            std::copy(words.begin() + 1, words.end(), std::ostream_iterator<string>(print, " "));
            output(print.str());
            output("\n");
        }
        else if (words[0] == "Game" && words[1] == "Over" && internal)
        {
            output("Game Over!\n");
            status = 0;
        }
        else if (!internal)
        {
            output("Invalid Command\n");
        }
    }
    check_triggers("", containers, master_list);
    triggers_run = internal ? true : false;
    return status;
}

int Game::parse_command(vec_str commands)
{
    int status = 1;
    for (string command : commands)
    {
        status *= parse_command(command, true);
    }
    return status;
}

int Game::parse_command(std::vector<vec_str> commands)
{
    int status = 1;
    for (auto command : commands)
    {
        status *= parse_command(command);
    }
    return status;
}