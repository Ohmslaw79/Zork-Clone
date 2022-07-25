#ifndef CONTAINER_H_
#define CONTAINER_H_
#include "forward.h"
#include "game_obj.h"

class container : public game_obj
{
private:
    set_str accept;
    set_str items;

public:
    container();

    void add_accepted_item(const string new_item);
    bool add_item(const string new_item);

    std::string take_item(const string item_to_remove);
    virtual void remove(const string item_to_remove);

    set_str get_items() const;
    virtual bool has(const string item) const;
    bool accepts(const string item) const;
    bool can_be_opened();

    virtual string get_inventory() const;
};

#endif /* CONTAINER_H_ */
