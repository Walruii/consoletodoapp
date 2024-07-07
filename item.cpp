#include "item.hpp"
#include "enums.hpp"
#include <iostream>

// Constructor
Item::Item(int id, const std::string &title)
    : id(id), title(title), check(false), indent_level(0) {}

// Accessors
std::string Item::get_title() const { return title; }

bool Item::get_check() const { return check; }

int Item::get_id() const { return id; }
int Item::get_indent_level() const { return indent_level; }

// Mutators
void Item::set_check(bool chk) { check = chk; }
void Item::set_indent_level(Directions dir) {
  if (dir == RIGHT) {
    indent_level++;
  } else if (dir == LEFT && indent_level > 0) {
    indent_level--;
  }
};

// Helper function to trim from the start
std::string ltrim(const std::string &s) {
  size_t start = s.find_first_not_of(" \t\n\r\f\v");
  return (start == std::string::npos) ? "" : s.substr(start);
}

// Helper function to trim from the end
std::string rtrim(const std::string &s) {
  size_t end = s.find_last_not_of(" \t\n\r\f\v");
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

// Function to trim from both ends
std::string trim(const std::string &s) { return rtrim(ltrim(s)); }

std::ostream &operator<<(std::ostream &os, const Item &item) {
  os << item.id << " " << item.check << " " << item.indent_level << " "
     << item.title << "\n";
  return os;
}

std::istream &operator>>(std::istream &is, Item &item) {
  is >> item.id;
  is >> item.check;
  is >> item.indent_level;
  std::string tmp;
  std::getline(is, tmp);
  item.title = trim(tmp);

  return is;
}
