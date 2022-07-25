#include "creature.h"

creature::creature()
{
    printv("Creating new creature");
}

void creature::add_vulnerability(string new_vulnerability)
{
    printv(get_name() + " - Adding Vulnerability: " + new_vulnerability);
    vulnerabilities.insert(new_vulnerability);
}
void creature::set_attack(trigger_ptr new_attack)
{
    printv(get_name() + " - Adding Attack");
    attack_trigger = new_attack;
}

bool creature::is_vulnerable(string attack)
{
    if (vulnerabilities.find(attack) != vulnerabilities.end())
    {
        return true;
    }
    return false;
}

vec_str creature::attack(std::map<string, container_ptr> containers, std::map<string, game_obj_ptr> items)
{
    vec_str output;
    if (attack_trigger != nullptr)
    {
        output = attack_trigger->run("", containers, items);
    }
    return output;
}