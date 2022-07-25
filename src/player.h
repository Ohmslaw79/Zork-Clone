#ifndef PLAYER_H_
#define PLAYER_H_
#include "forward.h"
#include "container.h"

class Player : public container{
    private:
    string current_room;
    std::set<string> opened_containers;

    public:
    Player();
    string get_current_room() const;
    void set_current_room(string new_room);
    void add_opened_container(string container);
    bool can_access(string container);
    std::set<string> can_access();
    string get_inventory();
    void add_to_inventory(string item);
};

typedef std::shared_ptr<Player> player_ptr;

#endif /* PLAYER_H_ */
