#ifndef CREATURE_H_
#define CREATURE_H_
#include "forward.h"
#include "game_obj.h"

class creature : public game_obj
{
private:
    set_str vulnerabilities;
    trigger_ptr attack_trigger = nullptr;

public:
    creature();
    void add_vulnerability(string new_vulnerability);
    void set_attack(trigger_ptr new_attack);
    bool is_vulnerable(string attack);
    vec_str attack(std::map<string, container_ptr> containers, std::map<string, game_obj_ptr> items);
};

typedef std::shared_ptr<creature> creature_ptr;

#endif /* CREATURE_H_ */
