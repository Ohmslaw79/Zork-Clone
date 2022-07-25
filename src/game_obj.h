#ifndef GAME_OBJ_H_
#define GAME_OBJ_H_
#include "forward.h"
#include "trigger.h"

class game_obj
{
private:
    string name = "";
    string status = "";
    string description = "";
    std::vector<trigger_ptr> triggers;

public:
    game_obj();
    string get_name() const;
    void set_name(string new_name);
    string get_status() const;
    void set_status(string new_status);
    string get_description() const;
    void set_description(string);
    void add_trigger(trigger_ptr);
    std::vector<vec_str> run_triggers(string input, std::map<string, container_ptr> containers, std::map<string, game_obj_ptr> items);
};
#endif /* GAME_OBJ_H_ */
