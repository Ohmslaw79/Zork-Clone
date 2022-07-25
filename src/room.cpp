#include "room.h"

room::room()
{
    printv("Creating new room");
}

std::string room::get_type() const
{
    return type;
}
void room::set_type(string new_type)
{
    printv(get_name() + " - Updating Type: " + new_type);
    type = new_type;
}
void room::add_border(vec_str new_boarder)
{
    printv(get_name() + " - Updating Boarder: " + new_boarder[0] + " - " + new_boarder[1]);
    boarders[new_boarder[0]] = new_boarder[1];
}
string room::get_border(string direction)
{
    return boarders[direction];
}

void room::add_container(string new_container)
{
    printv(get_name() + " - Adding Container: " + new_container);
    containers.insert(new_container);
}

void room::add_creature(string new_creature)
{
    printv(get_name() + " - Adding Creature: " + new_creature);
    creatures.insert(new_creature);
}

bool room::has(string object)
{
    return has_creature(object) || has_container(object) || container::has(object);
}

bool room::has_creature(string creature)
{
    bool has_creature = false;
    if (creatures.find(creature) != creatures.end())
    {
        has_creature = true;
    }
    return has_creature;
}
bool room::has_container(string container)
{
    bool has_creature = false;
    if (containers.find(container) != containers.end())
    {
        has_creature = true;
    }
    return has_creature;
}

void room::remove(string item_to_remove)
{
    container::remove(item_to_remove);
    for (string container : containers)
    {
        if (container == item_to_remove)
        {
            containers.erase(container);
            break;
        }
    }
    for (string creature : creatures)
    {
        if (creature == item_to_remove)
        {
            creatures.erase(creature);
            break;
        }
    }
}