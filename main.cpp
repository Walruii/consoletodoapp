#include "todo.hpp"
#include <iostream>
#include <ncurses.h>

#define PAGE_SIZE 10

void test() {}

int main() {
  // init screen sets up memory and clears the screen
  Todo todo;
  initscr();
  cbreak();
  curs_set(0);

  int start_x = 0;
  int start_y = 0;
  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  int choice;
  int highlight = 0;
  int page_number = 0;

  while (true) {
    // Creating a window
    int height = 10 + 6;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *menuwin = newwin(height, xMax, start_y, start_x);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    box(menuwin, 0, 0);

    // Top line display
    mvwprintw(menuwin, 0, 1, "TODOs");

    // Item Display
    int display = 0;
    for (int i = (page_number)*PAGE_SIZE;
         i < (page_number + 1) * PAGE_SIZE && i < todo.get_items_size(); i++) {
      if (i == highlight) {
        wattron(menuwin, A_REVERSE);
      }
      std::string indent_str(todo.items[i].get_indent_level() * 2, ' ');
      mvwprintw(menuwin, display + 1, 1, "%s[%s]%s", indent_str.c_str(),
                (todo.items[i].get_check()) ? "X" : " ",
                todo.items[i].get_title().c_str());
      wattroff(menuwin, A_REVERSE);
      display++;
    }

    // add Todo line
    if (highlight == display) {
      wattron(menuwin, A_REVERSE);
    }
    mvwprintw(menuwin, display + 1, 1, "Add Todo");
    wattroff(menuwin, A_REVERSE);

    // Page line
    if (highlight == display + 1) {
      wattron(menuwin, A_REVERSE);
    }
    mvwprintw(menuwin, display + 2, 1, "Page");
    wattroff(menuwin, A_REVERSE);

    // Last options line
    mvwprintw(menuwin, height - 2, 1,
              "vim mode\tCheck: Enter\tDelete: d\tIndent: hl");

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
      if (highlight > display + 1) {
        highlight = display + 1;
      }
      break;
    case 'd':
      if (highlight >= display)
        break;
      todo.delete_item(highlight);
      erase();
      break;
    case 'h':
      if (highlight >= display) {
        if (page_number > 0) {
          page_number--;
        }
      } else {
        todo.indent(todo.items[highlight], LEFT);
      }
      erase();
      break;
    case 'l':
      if (highlight >= display) {
        if (page_number > (todo.get_items_size() / PAGE_SIZE)) {

        } else {
          page_number++;
        }
      } else {
        todo.indent(todo.items[highlight], RIGHT);
      }
      erase();
      break;
    case 10:
      if (highlight == display) {
        char input[256];
        mvprintw(0, 0, "Add a todo: ");
        refresh();
        wrefresh(menuwin);
        getnstr(input, 256);
        todo.add_item(input);
        break;
      } else if (highlight == todo.get_items_size() + 1)
        break;
      todo.check_item(todo.items[highlight]);
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
