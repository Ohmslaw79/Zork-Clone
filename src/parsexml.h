#ifndef PARSEXML_H_
#define PARSEXML_H_

#include "forward.h"
#include "tinyxml.h"
#include "trigger.h"
#include "condition.h"
#include "container.h"
#include "creature.h"
#include "item.h"
#include "room.h"
#include "game.h"

game_ptr load_xml(string filename);

room_ptr parse_room(TiXmlElement *element);
trigger_ptr parse_trigger(TiXmlElement *element);
condition parse_condition(TiXmlElement *element);
vec_str parse_boarder(TiXmlElement *element);
container_ptr parse_container(TiXmlElement *element);
creature_ptr parse_creature(TiXmlElement *element);
item_ptr parse_item(TiXmlElement *element);
#endif