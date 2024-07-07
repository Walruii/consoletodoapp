#ifndef ITEM_HPP
#define ITEM_HPP

#include "enums.hpp"
#include <iostream>
#include <string>

class Item {
  std::string title;
  bool check;
  int id;
  int indent_level;

public:
  // Constructor
  Item(int id, const std::string &title);

  // Accessors
  std::string get_title() const;
  bool get_check() const;
  int get_id() const;
  int get_indent_level() const;

  // Mutators
  void set_check(bool chk);
  void set_indent_level(Directions dir);

  // Friend functions for stream operators
  friend std::ostream &operator<<(std::ostream &os, const Item &item);
  friend std::istream &operator>>(std::istream &is, Item &item);
};

#endif // ITEM_HPP
