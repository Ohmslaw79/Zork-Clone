#ifndef TRIGGER_H_
#define TRIGGER_H_
#include "forward.h"
#include "condition.h"

class trigger
{
private:
    std::vector<condition> conditions;
    bool permanent = false;
    bool has_run = false;
    set_str commands;
    vec_str message;
    set_str actions;

public:
    trigger();
    void add_condition(condition new_cnd);
    void add_message(string new_text);
    void add_action(string new_action);
    void is_permanent(bool new_param);
    void add_command(string new_commands);
    vec_str run(string input, std::map<string, container_ptr> containers, std::map<string, game_obj_ptr> items);
};

typedef std::shared_ptr<trigger> trigger_ptr;

#endif /* TRIGGER_H_ */
