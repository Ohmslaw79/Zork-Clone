#include "game_obj.h"

game_obj::game_obj()
{
    printv("Creating new game_obj");
}

string game_obj::get_name() const
{
    return name;
}

void game_obj::set_name(string new_name)
{
    name == "" ? printv("Setting Name: " + new_name) : printv(name + " - Updating Name: " + new_name);
    name = new_name;
}

string game_obj::get_status() const
{
    return status;
}

void game_obj::set_status(string new_status)
{
    printv(name + " - Updating Status: " + new_status);
    status = new_status;
}

string game_obj::get_description() const
{
    return description;
}

void game_obj::set_description(string new_description)
{
    printv(name + " - Updating Description: " + new_description);
    description = new_description;
}

void game_obj::add_trigger(trigger_ptr new_trigger)
{
    printv(name + " - Adding Trigger");
    triggers.push_back(new_trigger);
}

std::vector<vec_str> game_obj::run_triggers(string input, std::map<string, container_ptr> containers, std::map<string, game_obj_ptr> items)
{
    std::vector<vec_str> output;
    for (auto trigger : triggers)
    {
        output.push_back(trigger->run(input, containers, items));
    }
    return output;
}