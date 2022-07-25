#include "parsexml.h"

game_ptr load_xml(string filename)
{
    game_ptr game_instance(new Game());

    TiXmlDocument doc(filename);
    doc.LoadFile();
    if (doc.Error() != true)
    {

        TiXmlNode *root_element = doc.RootElement();

        for (TiXmlNode *node = root_element->FirstChild(); node != NULL;
             node = node->NextSibling())
        {
            TiXmlElement *child_element = node->ToElement();

            if (child_element != NULL)
            {
                string key = child_element->Value();
                if (key == "room")
                {
                    game_instance->add_room(parse_room(child_element));
                }
                else if (key == "container")
                {
                    game_instance->add_container(parse_container(child_element));
                }
                else if (key == "creature")
                {
                    game_instance->add_creature(parse_creature(child_element));
                }
                else if (key == "item")
                {
                    game_instance->add_item(parse_item(child_element));
                }
            }
        }
    }
    return game_instance;
}

room_ptr parse_room(TiXmlElement *element)
{
    printv("----------------------");
    room_ptr new_room(new room());

    for (TiXmlNode *node = element->FirstChild(); node != NULL;
         node = node->NextSibling())
    {

        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            string key = child_element->Value();

            if (key == "name")
            {
                new_room->set_name(child_element->GetText());
            }
            else if (key == "status")
            {
                new_room->set_status(child_element->GetText());
            }
            else if (key == "description")
            {
                new_room->set_description(child_element->GetText());
            }
            else if (key == "trigger")
            {
                new_room->add_trigger(parse_trigger(child_element));
            }
            else if (key == "type")
            {
                new_room->set_type(child_element->GetText());
            }
            else if (key == "border")
            {
                new_room->add_border(parse_boarder(child_element));
            }
            else if (key == "container")
            {
                new_room->add_container(child_element->GetText());
            }
            else if (key == "item")
            {
                new_room->add_item(child_element->GetText());
            }
            else if (key == "creature")
            {
                new_room->add_creature(child_element->GetText());
            }
        }
    }
    return new_room;
}

trigger_ptr parse_trigger(TiXmlElement *element)
{
    trigger_ptr new_trigger(new trigger());

    for (TiXmlNode *node = element->FirstChild(); node != NULL;
         node = node->NextSibling())
    {

        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            string key = child_element->Value();

            if (key == "condition")
            {
                new_trigger->add_condition(parse_condition(child_element));
            }
            else if (key == "type")
            {
                new_trigger->is_permanent(child_element->GetText() == string("permanent"));
            }
            else if (key == "command")
            {
                new_trigger->add_command(child_element->GetText());
            }
            else if (key == "print")
            {
                new_trigger->add_message(child_element->GetText());
            }
            else if (key == "action")
            {
                new_trigger->add_action(child_element->GetText());
            }
        }
    }
    return new_trigger;
}

condition parse_condition(TiXmlElement *element)
{
    condition new_condition;

    for (TiXmlNode *node = element->FirstChild(); node != NULL;
         node = node->NextSibling())
    {

        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            string key = child_element->Value();

            if (key == "has")
            {
                new_condition.set_has(child_element->GetText() == string("yes"));
            }
            else if (key == "status")
            {
                new_condition.set_status(child_element->GetText());
            }
            else if (key == "owner")
            {
                new_condition.set_owner(child_element->GetText());
            }
            else if (key == "object")
            {
                new_condition.set_object(child_element->GetText());
            }
        }
    }
    return new_condition;
}

vec_str parse_boarder(TiXmlElement *element)
{
    string direction;
    string room;

    for (TiXmlNode *node = element->FirstChild(); node != NULL;
         node = node->NextSibling())
    {

        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            string key = child_element->Value();

            if (key == "direction")
            {
                direction = child_element->GetText();
            }
            else if (key == "name")
            {
                room = child_element->GetText();
            }
        }
    }
    vec_str boarders{direction, room};
    return boarders;
}

container_ptr parse_container(TiXmlElement *element)
{
    printv("----------------------");
    container_ptr new_container(new container());

    for (TiXmlNode *node = element->FirstChild(); node != NULL;
         node = node->NextSibling())
    {

        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            string key = child_element->Value();

            if (key == "name")
            {
                new_container->set_name(child_element->GetText());
            }
            else if (key == "status")
            {
                new_container->set_status(child_element->GetText());
            }
            else if (key == "description")
            {
                new_container->set_description(child_element->GetText());
            }
            else if (key == "trigger")
            {
                new_container->add_trigger(parse_trigger(child_element));
            }
            else if (key == "type")
            {
                new_container->set_status(child_element->GetText());
            }
            else if (key == "accept")
            {
                new_container->add_accepted_item(child_element->GetText());
            }
            else if (key == "item")
            {
                new_container->add_item(child_element->GetText());
            }
        }
    }
    return new_container;
}

creature_ptr parse_creature(TiXmlElement *element)
{
    printv("----------------------");
    creature_ptr new_creature(new creature());

    for (TiXmlNode *node = element->FirstChild(); node != NULL;
         node = node->NextSibling())
    {

        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            string key = child_element->Value();

            if (key == "name")
            {
                new_creature->set_name(child_element->GetText());
            }
            else if (key == "status")
            {
                new_creature->set_status(child_element->GetText());
            }
            else if (key == "description")
            {
                new_creature->set_description(child_element->GetText());
            }
            else if (key == "trigger")
            {
                new_creature->add_trigger(parse_trigger(child_element));
            }
            else if (key == "type")
            {
                new_creature->set_status(child_element->GetText());
            }
            else if (key == "vulnerability")
            {
                new_creature->add_vulnerability(child_element->GetText());
            }
            else if (key == "attack")
            {
                new_creature->set_attack(parse_trigger(child_element));
            }
        }
    }
    return new_creature;
}

item_ptr parse_item(TiXmlElement *element)
{
    printv("----------------------");
    item_ptr new_item(new item());

    for (TiXmlNode *node = element->FirstChild(); node != NULL;
         node = node->NextSibling())
    {

        TiXmlElement *child_element = node->ToElement();
        if (child_element != NULL)
        {
            string key = child_element->Value();

            if (key == "name")
            {
                new_item->set_name(child_element->GetText());
            }
            else if (key == "status")
            {
                new_item->set_status(child_element->GetText());
            }
            else if (key == "description")
            {
                new_item->set_description(child_element->GetText());
            }
            else if (key == "trigger")
            {
                new_item->add_trigger(parse_trigger(child_element));
            }
            else if (key == "type")
            {
                new_item->set_status(child_element->GetText());
            }
            else if (key == "writing")
            {
                new_item->set_writing(child_element->GetText());
            }
            else if (key == "turnon")
            {
                for (TiXmlNode *child_node = node->FirstChild(); child_node != NULL;
                     child_node = child_node->NextSibling())
                {

                    TiXmlElement *turnon_element = child_node->ToElement();
                    if (turnon_element != NULL)
                    {
                        string turnon_key = turnon_element->Value();
                        if (turnon_key == "action")
                        {
                            new_item->set_action(turnon_element->GetText());
                        }
                        else if (turnon_key == "print")
                        {
                            new_item->set_print(turnon_element->GetText());
                        }
                    }
                }
            }
        }
    }
    return new_item;
}