#ifndef TODO_HPP
#define TODO_HPP

#include "enums.hpp"
#include "item.hpp"
#include <iostream>
#include <string>
#include <vector>

class Todo {
  int serial_no;

public:
  std::vector<Item> items;
  Todo();
  void add_item(std::string title);
  int get_items_size();
  std::vector<Item> get_items();
  void delete_item(int index);
  void update_serial_no();
  void check_item(Item &item);
  void update_item(Item &item);
  void indent(Item &item, Directions dir);
};

#endif
