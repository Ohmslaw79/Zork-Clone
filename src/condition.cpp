#include "condition.h"
#include "container.h"
#include "game_obj.h"

condition::condition()
{
    printv("Creating new condition");
}

condition::condition(bool _has, string _status, string _owner) : has(_has), status(_status), owner(_owner) {}

void condition::set_has(bool new_param)
{
    printv(string("  --Updating has to ") + (new_param ? "true" : "false"));
    has = new_param;
}
void condition::set_status(string new_status)
{
    printv("  --Updating Status: " + new_status);
    status = new_status;
}
void condition::set_owner(string new_owner)
{
    printv("  --Updating Owner: " + new_owner);
    owner = new_owner;
}

void condition::set_object(string new_object)
{
    printv("  --Updating Object: " + new_object);
    object = new_object;
}

bool condition::check(const std::map<string, container_ptr> containers, const std::map<string, game_obj_ptr> items) const
{
    bool owner_satisfied = false;
    bool item_satisfied = false;

    if (!owner.empty())
    {
        if (containers.at(owner)->has(object) == has)
        {
            owner_satisfied = true;
        }
    }
    else
    {
        owner_satisfied = true;
    }
    if (!object.empty())
    {
        game_obj_ptr item = items.at(object);
        if (status.empty() || item->get_status() == status)
        {
            item_satisfied = true;
        }
    }
    else
    {
        item_satisfied = true;
    }
    return owner_satisfied && item_satisfied;
}