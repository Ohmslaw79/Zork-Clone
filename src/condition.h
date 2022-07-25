#ifndef CONDITION_H_
#define CONDITION_H_
#include "forward.h"

class condition
{
private:
    bool has = true;
    string object;
    string status;
    string owner;

public:
    condition();
    condition(bool _has, string status, string owner);
    void set_has(bool new_param);
    void set_status(string new_status);
    void set_owner(string new_owner);
    void set_object(string new_object);

    bool check(const std::map<string, container_ptr> containers, const std::map<string, game_obj_ptr> items) const;
};

#endif /* CONDITION_H_ */
