#include "trigger.h"
#include "game_obj.h"
trigger::trigger()
{
    printv("Creating new trigger");
}

void trigger::add_condition(condition new_cnd)
{
    printv(" -Adding Condition");
    conditions.push_back(new_cnd);
}

void trigger::add_message(string new_text)
{
    printv(" -Adding Message: " + new_text);
    message.push_back(new_text);
}

void trigger::add_action(string new_action)
{
    printv(" -Adding Action: " + new_action);
    actions.insert(new_action);
}

void trigger::is_permanent(bool new_param)
{
    printv(string(" -Setting trigger to ") + (new_param ? "permanent" : "single"));
    permanent = new_param;
}

void trigger::add_command(string new_command)
{
    printv(" -Adding Command: " + new_command);
    commands.insert(new_command);
}

vec_str trigger::run(string input, std::map<string, container_ptr> containers, std::map<string, game_obj_ptr> items)
{
    vec_str output;
    if ((commands.empty() || (commands.find(input) != commands.end())) && (permanent || !has_run))
    {
        bool conditions_satisfied = true;
        for (auto condition : conditions)
        {
            conditions_satisfied = condition.check(containers, items) && conditions_satisfied;
        }
        if (conditions_satisfied)
        {
            std::ostringstream messages;
            std::copy(message.begin(), message.end(), std::ostream_iterator<string>(messages, " "));
            output.push_back("print " + messages.str());
            for (auto it = actions.rbegin(); it != actions.rend(); it++)
            {
                output.push_back(*it);
            }
            has_run = true;
        }
    }
    return output;
}