#ifndef ROOM_H_
#define ROOM_H_
#include "forward.h"
#include "container.h"

class room : public container{
    private:
    string type = "regular";
    std::map<string, string> boarders = {
        {"north", ""},
        {"south", ""},
        {"east", ""},
        {"west", ""}
    };
    set_str containers;
    set_str creatures;

    public:
    room();

    string get_type() const;
    void set_type(string new_type);
    string get_border(string direction);
    void add_border(vec_str new_boarder);
    void add_container(string new_container);
    void add_creature(string new_creature);
    bool has(string object);
    bool has_creature(string creature);
    bool has_container(string container);
    void remove(string item_to_remove);
};

typedef std::shared_ptr<room> room_ptr;

#endif /* ROOM_H_ */
