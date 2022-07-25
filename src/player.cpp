#include "player.h"

Player::Player() : container()
{
    opened_containers.insert(inventory);
}

string Player::get_current_room() const
{
    return current_room;
}

void Player::set_current_room(string new_room)
{
    current_room = new_room;
}

void Player::add_opened_container(string container)
{
    opened_containers.insert(container);
}

bool Player::can_access(string container)
{
    bool can_access = false;
    if (current_room == container)
    {
        can_access = true;
    }
    else if (opened_containers.find(container) != opened_containers.end())
    {
        can_access = true;
    }
    return can_access;
}

std::set<string> Player::can_access()
{
    std::set<string> accessable = opened_containers;
    accessable.insert(current_room);
    return accessable;
}

string Player::get_inventory()
{
    string inventory_string = "Inventory: ";
    if (get_items().size() == 0)
    {
        inventory_string.append("Empty\n");
    }
    else
    {
        set_str items = get_items();
        for (auto item : items)
        {
            inventory_string.append(item + (next(items.find(item)) != items.end() ? ", " : ""));
        }
        inventory_string.append("\n");
    }
    return inventory_string;
}

void Player::add_to_inventory(string item)
{
    if (!item.empty())
    {
        add_item(item);
    }
}