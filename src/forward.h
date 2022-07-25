#ifndef FORWARD_H_
#define FORWARD_H_
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
//#define VERBOSE
#define inventory "inventory"

typedef std::string string;
typedef std::vector<string> vec_str;
typedef std::set<string> set_str;

void printd(string);
void printv(string);

class condition;
class container;
class creature;
class Game;
class game_obj;
class item;
class Player;
class room;
class trigger;

typedef std::shared_ptr<container> container_ptr;
typedef std::shared_ptr<item> item_ptr;
typedef std::shared_ptr<game_obj> game_obj_ptr;
#endif /* FORWARD_H_ */
