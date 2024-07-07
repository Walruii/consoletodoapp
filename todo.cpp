#include "todo.hpp"
#include <fstream>

// Construstor
Todo::Todo() : serial_no(0) {
  std::ifstream fin;
  fin.open("todos.txt");
  if (!fin.is_open()) {
    std::cerr << "Error opening file todos!" << std::endl;
    return;
  }
  Item i1(-1, "");
  int serial;
  fin >> serial;
  serial_no = serial;
  while (fin >> i1) {
    items.push_back(i1);
  }
  fin.close();
}

// Getters
int Todo::get_items_size() { return items.size(); }
std::vector<Item> Todo::get_items() { return items; }

// Setters
void Todo::check_item(Item &item) {
  item.set_check(!item.get_check());
  update_item(item);
}
void Todo::indent(Item &item, Directions dir) {
  item.set_indent_level(dir);
  update_item(item);
};

// Update the serial_no in file
void Todo::update_serial_no() {
  // Open the file in read mode
  std::ifstream inFile("todos.txt");
  if (!inFile) {
    inFile.close();
    std::ofstream outFile("todos.txt");
    outFile << serial_no << "\n";
    outFile.close();
    /* std::cerr << "Error opening file for reading: todos.txt" << std::endl; */
    return;
  }

  // Read all lines into a vector
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inFile, line)) {
    lines.push_back(line);
  }
  inFile.close();

  // Modify the first line
  if (!lines.empty()) {
    lines[0] = std::to_string(serial_no);
  } else {
    // If the file was empty, add the new first line
    lines.push_back(std::to_string(serial_no));
  }

  // Open the file in write mode
  std::ofstream outFile("todos.txt");
  if (!outFile) {
    std::cerr << "Error opening file for writing: todos.txt" << std::endl;
    return;
  }

  // Write all lines back to the file
  for (const auto &l : lines) {
    outFile << l << '\n';
  }
  outFile.close();
}

// add the item to vector and file
void Todo::add_item(std::string title) {
  serial_no++;
  Item item(serial_no, title);
  update_serial_no();
  items.push_back(item);
  std::ofstream of;
  of.open("todos.txt", std::ios_base::app);
  of << item;
  of.close();
}

// deleting an item from vector and file
void Todo::delete_item(int index) {
  int id = items[index].get_id();
  items.erase(items.begin() + index);

  std::ifstream fin;
  fin.open("todos.txt");
  if (!fin) {
    std::cerr << "Error opening input file: todos.txt" << std::endl;
    return;
  }

  int serial;
  fin >> serial;
  std::vector<Item> fileItems;
  Item it(-1, "");
  while (fin >> it) {
    if (it.get_id() != id) {
      fileItems.push_back(it);
    }
  }
  fin.close();

  std::ofstream fout("todos.txt");
  if (!fout) {
    std::cerr << "Error opening output file: todos.txt" << std::endl;
    return;
  }
  fout << serial_no << "\n";
  for (const auto &item : fileItems) {
    fout << item;
  }
  fout.close();
}

// updating an item in file
void Todo::update_item(Item &item) {
  std::ifstream fin;
  fin.open("todos.txt");
  if (!fin) {
    std::cerr << "Error opening input file: todos.txt" << std::endl;
    return;
  }

  int serial;
  fin >> serial;
  std::vector<Item> fileItems;
  Item it(-1, "");
  while (fin >> it) {
    if (it.get_id() != item.get_id()) {
      fileItems.push_back(it);
    } else {
      fileItems.push_back(item);
    }
  }
  fin.close();

  std::ofstream fout("todos.txt");
  if (!fout) {
    std::cerr << "Error opening output file: todos.txt" << std::endl;
    return;
  }
  fout << serial_no << "\n";
  for (const auto &item : fileItems) {
    fout << item;
  }
  fout.close();
}
