#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

class Item {
  std::string title;
  bool check;
  int id;

public:
  std::string get_title() { return title; }
  Item(int id, std::string title) : id(id), title(title), check(false){};
  bool get_check() { return check; }
  void set_check(bool chk) { check = chk; }
  friend std::ostream &operator<<(std::ostream &os, const Item &item);
  friend std::istream &operator>>(std::istream &os, Item &item);
};

std::ostream &operator<<(std::ostream &os, const Item &item) {
  os << item.id << " " << item.title << " ";
  return os;
}
std::istream &operator>>(std::istream &is, Item &item) {
  is >> item.id >> item.title;
  return is;
}

class Todo {
  int serial_no;
public:
  std::vector<Item> items;

  Todo(): serial_no(0) {
    std::ifstream fin;
    fin.open("todos.txt");
    if (!fin.is_open()) {
      std::cerr << "Error opening file todos!" << std::endl;
      return;
    }
    Item i1(-1, "");
    /* int serial; */
    /* fin >> serial; */
    /* serial_no = serial; */
    while (fin >> i1) {
      items.push_back(i1);
    }
    fin.close();
  }

  void addItem(std::string title) {
    serial_no++;
    Item item(serial_no, title);
    items.push_back(item);
    std::ofstream of;
    of.open("todos.txt", std::ios_base::app);
    of << item;
    of.close();
  }

  int get_items_size() { return items.size(); }
  std::vector<Item> get_items() { return items; }

  void delete_item(int index) { 
    items.erase(items.begin() + index); 
  }
};

int main() {
  // init screen
  // sets up memory and clears the screen
  Todo todo;
  initscr();
  cbreak();
  curs_set(0);
  /* noecho(); */

  int height, width, start_y, start_x;
  height = todo.get_items_size() + 3;
  width = 20;
  start_y = start_x = 0;

  int x, y, yBed, xBeg, yMax, xMax;
  getyx(stdscr, y, x);
  getmaxyx(stdscr, yMax, xMax);

  int choice;
  int highlight = 0;

  while (true) {
    height = todo.get_items_size() + 3;
    getyx(stdscr, y, x);
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *menuwin = newwin(height, xMax, 0, start_x);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    box(menuwin, 0, 0);
    mvwprintw(menuwin, 0, 1, "TODOs:");
    for (int i = 0; i < todo.get_items_size(); i++) {
      if (i == highlight) {
        wattron(menuwin, A_REVERSE);
      }
      mvwprintw(menuwin, i + 1, 1, "[%s]%s",
                (todo.items[i].get_check()) ? " " : "X",
                todo.items[i].get_title().c_str());
      wattroff(menuwin, A_REVERSE);
    }

    if (highlight == todo.get_items_size()) {
      wattron(menuwin, A_REVERSE);
    }
    mvwprintw(menuwin, todo.get_items_size() + 1, 1, "Add Todo");
    wattroff(menuwin, A_REVERSE);

    choice = wgetch(menuwin);
    switch (choice) {
    case 'k':
      highlight--;
      if (highlight < 0) {
        highlight = 0;
      }
      break;
    case 'j':
      highlight++;
      if (highlight > todo.get_items_size()) {
        highlight = todo.get_items_size();
      }
      break;
    case 'd':
      if (highlight >= todo.get_items_size())
        break;
      todo.delete_item(highlight);
      erase();
      break;
    case 10:
      if (highlight >= todo.get_items_size()) {
        char input[256];
        mvprintw(0, 0, "Add a todo: ");
        refresh();
        wrefresh(menuwin);
        getnstr(input, 256);
        todo.addItem(input);
        break;
      }
      todo.items[highlight].set_check(!todo.items[highlight].get_check());
      break;

    default:
      break;
    }
    if (choice == 'q') {
      break;
    }
  }
  endwin();
  // deallocates memeory and ends ncurses
}

/* int x, y; */
/* x = y = 10; */
// moves the cursor to the specified location
/* move(y, x); */
// prints a string(const char*) to a window
/* printw("Hello World"); */
// refreshes the screen to match whats in memory
/* refresh(); */
// waits for user input, return in tvalue of that key
/* clear(); */
/* move(0, 0); */
/* printw("%c", c); */
/* getch(); */
/* if (!has_colors()) { */
/*   printw("Terminal does not support color"); */
/*   getch(); */
/*   return -1; */
/* } */
/* start_color(); */
