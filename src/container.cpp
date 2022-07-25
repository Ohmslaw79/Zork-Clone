#include "container.h"
#include <bits/stdc++.h>

container::container()
{
    printv("Creating new container");
}

void container::add_accepted_item(const string new_item)
{
    printv(get_name() + " - Adding Accepted Item: " + new_item);
    accept.insert(new_item);
}

bool container::add_item(const string new_item)
{
    bool item_added = false;
    if (accept.empty() || accept.find(new_item) != accept.end())
    {
        printv(get_name() + " - Adding Item: " + new_item);
        items.insert(new_item);
        item_added = true;
    }

    return item_added;
}

string container::take_item(const string item_to_remove)
{
    string removed_item;

    for (string item : items)
    {
        if (item == item_to_remove)
        {
            removed_item = item;
            items.erase(item);
            break;
        }
    }
    removed_item.empty() ? printd("Failed to remove" + item_to_remove) : printd("Successfully Removed" + removed_item);
    return removed_item;
}

void container::remove(const string item_to_remove)
{
    printv(get_name() + " - Removing " + item_to_remove + "\n");
    for (string item : items)
    {
        if (item == item_to_remove)
        {
            items.erase(item);
            break;
        }
    }
}

set_str container::get_items() const
{
    return items;
}

bool container::has(const string item) const
{
    return items.find(item) != items.end();
}

bool container::accepts(const string item) const
{
    return accept.find(item) != accept.end();
}

bool container::can_be_opened()
{
    bool satisfied = true;
    if (!accept.empty())
    {
        for(auto item : accept){
            satisfied = has(item) && satisfied;
        }
    }
    return satisfied;
}

string container::get_inventory() const
{
    string inventory_string = "The " + get_name() + " ";
    if (get_items().size() == 0)
    {
        inventory_string.append("is empty\n");
    }
    else
    {
        inventory_string.append("contains: ");

        set_str items = get_items();
        for (auto item : items)
        {
            inventory_string.append(item + (next(items.find(item)) != items.end() ? ", " : ""));
        }
        inventory_string.append("\n");
    }
    return inventory_string;
}