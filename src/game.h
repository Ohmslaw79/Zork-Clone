#ifndef GAME_H_
#define GAME_H_
#include "forward.h"
#include "condition.h"
#include "game_obj.h"
#include "container.h"
#include "creature.h"
#include "item.h"
#include "room.h"
#include "player.h"

class Game
{
private:
    std::map<string, game_obj_ptr> master_list;
    std::map<string, room_ptr> rooms;
    std::map<string, container_ptr> containers;
    std::map<string, creature_ptr> creatures;
    std::map<string, item_ptr> items;
    player_ptr player;
    bool triggers_run = false;

    void take_item(string item);
    void drop_item(string item);
    void put_item(string item, string container);
    void read(string item);
    void update_status(string object, string new_status);
    void read_item(string item);
    void move(string direction);
    void open(string container);
    int exit();
    int check_triggers(string input, std::map<string, container_ptr> containers, std::map<string, game_obj_ptr> items);
    void output(string text);
    void attack_creature(string creature, string weapon);

public:
    Game();
    void add_room(const room_ptr room);
    void add_container(const container_ptr container);
    void add_creature(const creature_ptr creature);
    void add_item(const item_ptr item);
    void set_room(string new_room);
    void start_game(string starting_room);

    int parse_command(string command, bool internal);
    int parse_command(vec_str commands);
    int parse_command(std::vector<vec_str> commands);
};

typedef std::shared_ptr<Game> game_ptr;
#endif /* GAME_H_ */
