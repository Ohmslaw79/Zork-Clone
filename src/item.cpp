#include "item.h"

item::item()
{
    printv("Creating new item");
}

void item::set_writing(std::string new_writing)
{
    printv(get_name() + " - Updating Writing: " + new_writing);
    writing = new_writing;
}

std::string item::get_writing() const
{
    return writing;
}

void item::set_action(string new_action)
{
    printv(get_name() + " - Setting Action: " + new_action);
    action = new_action;
}

void item::set_print(string new_print)
{
    printv(get_name() + " - Setting print: " + new_print);
    print = new_print;
}

vec_str item::turn_on()
{
    vec_str output;
    output.push_back("print " + print);
    output.push_back(action);
    return output;
}