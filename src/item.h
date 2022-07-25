#ifndef ITEM_H_
#define ITEM_H_
#include "forward.h"
#include "game_obj.h"

class item : public game_obj
{
private:
    string writing;
    string action;
    string print;

public:
    item();
    string get_writing() const;
    void set_writing(string new_writing);
    void set_action(string new_action);
    void set_print(string new_print);
    vec_str turn_on();
};

#endif /* ITEM_H_ */