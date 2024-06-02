#include <iostream>
#include <ncurses.h>
using namespace std;

int main() {
  // init screen
  // sets up memory and clears the screen
  initscr();
  cbreak();
  noecho();

  int height, width, start_y, start_x;
  height = 10;
  width = 20;
  start_y = start_x = 10;

  WINDOW *win = newwin(height, width, start_y, start_x);

  refresh();

  box(win, 0, 0);

  mvwprintw(win, 1, 1, "this is my box");

  wrefresh(win);

  int c = getch();


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
